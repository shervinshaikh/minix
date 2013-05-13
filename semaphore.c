#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "semaphore.h"

#define OK 0
#define EPERM 1
#define EINVAL 2
#define EDONTREPLY 3
#define ENOMEM 4


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

int main(void)
{

	debug("Semaphore service is now running..........");
	// because its defined in glo.h
	// message m;
	// endpoint_t who_e, call_nr;
	int result;

	/* SEF local startup. */
	// sef_startup();

	// initalize 20 empty semaphores
	int k;
	for(k=0; k<10; k++){
		semaphores[k] = (struct Semaphore*) malloc(sizeof(struct Semaphore*));
		semaphores[k]->q = init_queue();
		semaphores[k]->isValid = 0;
	}

	// hard code some tests to see if semaphore services works
	int semNumber = do_sem_init(3);
	debug("size of queue of first semaphore: %d", queue_size(semaphores[0]->q));
	int semNumber2 = do_sem_init(2);
	do_sem_down(semNumber, 111);
	do_sem_down(semNumber, 222);
	do_sem_down(semNumber, 333);
	do_sem_down(semNumber, 444);
	//do_sem_up(semNumber);


	return 0;
}

int do_sem_init(int start_value){
	if(start_value <= 0){
		return EPERM;
	}
	if(semaphores == NULL){ // out of memory failure
		return ENOMEM;
	}
	semaphores[nextValue]->value = start_value;
	semaphores[nextValue]->isValid = 1;

	debug("SEM_INIT, sem number: %d, start value: %d", nextValue, start_value);

	//if(nextValue == lastValue && arraySize > lastValue){
		nextValue++;
		return lastValue++;
	//}

	// // worry about this later
	// else if(arraySize == lastValue){
	// 	// we need to expand the array

	// }
	// else{
	// 	// go through array and see which one is the next available semaphore
	// 	while(semaphores[nextValue]->isValid == 1 && lastValue != nextValue){
	// 		nextValue++;
	// 	}
	// }
	// return nextValue++;
}

// COMPLETE
int do_sem_down(int semNumber, int source){
	if(semaphores[semNumber]->isValid == 0){
		return EINVAL;
	}
	else if(semaphores[semNumber]->value > 0){ // available semaphore then decresase
		semaphores[semNumber]->value--;
		debug("SEM_DOWN, sem number: %d, sem value: %d", semNumber, semaphores[semNumber]->value);
		return OK;
	}
	// add it to the queue and return not reply 
	debug("about to add pid: %d to the queue", source);
	debug("address of q->front: %p", semaphores[semNumber]->q);
	enqueue(semaphores[semNumber]->q, source);
	return EDONTREPLY;
}

// COMPLETE
int do_sem_up(int semNumber){
	debug("about to increase semaphore value");
	if(semaphores[semNumber]->isValid == 0){
		return EINVAL;
	}

	// add resource to that specific semaphore number
	semaphores[semNumber]->value++; 
	debug("SEM_UP, sem number: %d, new sem value: %d", semNumber, semaphores[semNumber]->value);

	if(queue_size(semaphores[semNumber]->q) > 0){ // if processes blocked on semaphore then remove process
		semaphores[semNumber]->value--;
		int source = dequeue(semaphores[semNumber]->q); // remove process from queue
		
		debug("process in queue, pid: %d", source);
		//sendnb(source, &m); 

		// message m;
		// m.m_type = OK;
		// m.m_source = dequeue(semaphores[semNumber]->q); // remove process from queue
		// sendnb(m.m_source, &m); // reply to unblock the process
	}

	return OK;
}

int do_sem_release(int semNumber){
	// set isValid to 0, and NULL all pointers
	semaphores[semNumber]->isValid = 0;
	semaphores[semNumber]->value = 0;
	semaphores[semNumber]->q = NULL;


	// change next available semaphore # and hold onto last spot in array

	return OK;
}

struct Queue* init_queue(){
	struct Queue* q = (struct Queue*) malloc(sizeof(struct Queue*));
	q->rear = NULL;
	q->front = NULL;
	q->size = 0;
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
	printf("null = %p\n", NULL);
	printf("about to check front of que, %p\n", q->front);
	if(q->front == NULL){
		printf("inside if statement");
		q->front = var;
		q->front->next = NULL;
		q->rear = q->front;
	}
	else{
		printf("inside else statement");
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

