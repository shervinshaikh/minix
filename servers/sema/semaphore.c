#include "semaphore.h"
#include <minix/keymap.h>
#include <minix/callnr.h>
#include <minix/com.h>
#include <minix/ds.h>
#include <minix/type.h>
#include <minix/endpoint.h>
#include <minix/minlib.h>
#include <minix/type.h>
#include <minix/vm.h>
#include <minix/crtso.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/utsname.h>
#include <string.h>
#include <machine/archtypes.h>
#include <env.h>
#include <stdio.h>
#include <minix/ipc.h>

#define DEBUG
#ifdef DEBUG
    #define    debug(f,...)    fprintf(stderr,f "\n",##__VA_ARGS__)
#else
    #define    debug(f,...)
#endif

struct Node
{
	int process;
	struct Node* next;
};

struct Queue
{
	int size;
	struct Node *rear, *front;
};

struct Semaphore
{
	int isValid; // 0 = is NOT initialized, 1 = is initialized
	int value;
	struct Queue *q;
};

int s = 1;
int nextValue = 0, lastValue = 0, arraySize = 10;
struct Semaphore *semaphores[10];

/*===========================================================================*
 *				main                                         *
 *===========================================================================*/
int main(void)
{

	debug("Semaphore service is now running..........");
	// because its defined in glo.h
	message m;
	endpoint_t who_e, call_nr;
	int result;

	/* SEF local startup. */
	sef_startup();

	// initalize 10 empty semaphores
	int k;
	for(k=0; k<10; k++){
		semaphores[k] = (struct Semaphore*) malloc(sizeof(struct Semaphore));
		semaphores[k]->q = init_queue();
		semaphores[k]->isValid = 0;
	}

	/* This is SEMAPHORE's main loop-  get work and do it, forever and forever. */
	while (TRUE) {
		int ipc_status;

		//debug("IN THE WHILE STATE FOR SEMA");

		/* wait for request message */
		//if ((result = sef_receive_status(ANY, &m, &ipc_status)) != OK)
		if ((result = receive(ANY, &m, &ipc_status)) != OK)
			debug("SEMAPHORE receive error %d", result);
		
		//debug("SEMAPHORE recieved a message");

		who_e = m.m_source;
		call_nr = m.m_type;

		// debug("Call Number: %d", call_nr);
		// debug("Who: %d", who_e);

		
		switch(call_nr){
			case SEM_INIT: result = do_sem_init(&m); break;
			case SEM_DOWN: result = do_sem_down(&m); break;
			case SEM_UP: result = do_sem_up(&m); break;
			case SEM_RELEASE: result = do_sem_release(&m); break;
			default: result = EINVAL;
		}

		if(result != EDONTREPLY){
			message m_out;
			m_out.m_type = result;
			sendnb(who_e, &m_out);
		}
		//result = (*call_vec[call_nr])();
	}

	/* impossible to get here */



	return 0;
}

int do_sem_init(message *m_ptr){
	int start_value = m_ptr->m1_i1;
	//debug("---------------  INIT");
	//debug("server, Start value: %d", start_value);

	if(start_value <= 0){
		return EPERM;
	}
	if(semaphores == NULL){ // out of memory failure
		return ENOMEM;
	}
	semaphores[nextValue]->value = start_value;
	semaphores[nextValue]->isValid = 1;

	debug("SEM_INIT, sem number: %d, start value: %d", nextValue, semaphores[nextValue]->value);
	nextValue++;
	return lastValue++;
}

int do_sem_down(message *m_ptr){
	int semNumber = m_ptr->m1_i2;
	int source = m_ptr->m_source;
	//debug("---------------  DOWN");
	//debug("server, Semaphore number: %d", semNumber);
	if(semaphores[semNumber]->isValid == 0){
		return EINVAL;
	}
	else if(semaphores[semNumber]->value > 0){ // available semaphore then decresase
		semaphores[semNumber]->value--;
		debug("SEM_DOWN old: %d, new: %d", semaphores[semNumber]->value+1, semaphores[semNumber]->value);
		return OK;
	}
	debug("about to add pid: %d to the queue", source);
	debug("address of q->front: %p", semaphores[semNumber]->q->front); 
	// add it to the queue and return not reply 
	enqueue(semaphores[semNumber]->q, source);
	return EDONTREPLY;
}

int do_sem_up(message *m_ptr){
	int semNumber = m_ptr->m1_i2;
	//debug("---------------  UP");
	//debug("server, Semaphore number: %d", semNumber);
	if(semaphores[semNumber]->isValid == 0){
		return EINVAL;
	}

	// add resource to that specific semaphore number
	semaphores[semNumber]->value++; 
	debug("SEM_UP, sem number: %d, new sem value: %d", semNumber, semaphores[semNumber]->value);

	if(queue_size(semaphores[semNumber]->q) > 0){ // if processes blocked on semaphore then remove process
		semaphores[semNumber]->value--;
		message m;
		m.m_type = OK;
		m.m_source = dequeue(semaphores[semNumber]->q); // remove process from queue
		sendnb(m.m_source, &m);
	}

	return OK;
}

int do_sem_release(message *m_ptr){
	int semNumber = m_ptr->m1_i3;
	debug("---------------  RELEASED");
	debug("server, Semaphore: %d", semNumber);

	/// set isValid to 0, and NULL all pointers
	semaphores[semNumber]->isValid = 0;
	semaphores[semNumber]->value = 0;
	semaphores[semNumber]->q = NULL;


	// change next available semaphore # and hold onto last spot in array

	return OK;
}




struct Queue* init_queue(){
	struct Queue* q = (struct Queue*) malloc(sizeof(struct Queue));
	q->rear = NULL;
	q->front = NULL;
	q->size = 0;
	debug("initalized a que, q->front address: %p", q->front);
	return q;
}

int dequeue(struct Queue* q){
	struct Node *temp = q->front;
	if(temp == NULL){
		// queue empty, should never reach here
		return -1;
	}
	q->front = q->front->next;
	temp->next = NULL;
	q->size--;
	return temp->process;
}

void enqueue(struct Queue* q, int process){
	struct Node *var = (struct Node*)malloc(sizeof(struct Node));
	var->process = process;
	//printf("null = %p\n", NULL);
	//printf("about to check front of que, %p\n", q->front);
	if(q->front == NULL){
		//printf("inside if statement");
		q->front = var;
		q->front->next = NULL;
		q->rear = q->front;
	}
	else{
		//printf("inside else statement");
		q->rear->next = var;
		q->rear = var;
		//front->next = NULL;
	}
	q->size++;
	printf("%d was added to the queue and the new size: %d\n", q->rear->process, q->size);
}


int queue_size(struct Queue* q){
	return q->size;
}