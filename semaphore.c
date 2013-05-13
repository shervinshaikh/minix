#include "queue.h"

#define DEBUG
#ifdef DEBUG
    #define    debug(f,...)    fprintf(stderr,f "\n",##__VA_ARGS__)
#else
    #define    debug(f,...)
#endif

int s = 1
int nextValue = 0, lastValue = 0, arraySize = 20;

struct Semaphore
{
	int isValid; // 0 = is NOT initialized, 1 = is initialized
	int value;
	struct Queue *q;
}

int main(void)
{

	debug("Semaphore service is now running..........");
	// because its defined in glo.h
	//message m;
	//endpoint_t who_e, call_nr;
	int result;

	/* SEF local startup. */
	//sef_startup();

	// initalize 20 empty semaphores
	int k;
	struct Semaphore semaphores[20];
	for(k=0; k<20; k++){
		semaphores[k] = (struct Semaphore*) malloc(sizeof(Semaphore));
		semaphores[k]->q = init_queue();
		semaphores[k]->isValid = 0;
	}

	// hard code some tests to see if semaphore services works
	int semNumber = do_sem_init(3);
	do_sem_down(semNumber);
	do_sem_down(semNumber);
	do_sem_down(semNumber);


	return 0;
}

int do_sem_init(int start_value){
	if(semaphores == NULL){ // out of memory failure
		return ENOMEM;
	}
	semaphores[nextValue] = start_value;

	if(nextValue == lastValue && arraySize > lastValue){
		nextValue++;
		return lastValue++;
	}
	else if(arraySize == lastValue){

	}
	else{
		// go through array and see which one is the next available semaphore
		while(semaphores[nextValue]->isValid == 1){
			nextValue++;
		}
	}
	return nextValue++;
}

// COMPLETE
int do_sem_down(int semNumber, int source){
	if(semaphores[semNumber]->isValid == 0){
		return EINVAL;
	}
	else(semaphores[semNumber]->value > 0){ // available semaphore then decresase
		semaphores[semNumber]->value--;	
		return OK;
	}
	// add it to the queue and return not reply 
	enqueue(semaphores->q, source);
	return EDONTREPLY;
}

// COMPLETE
int do_sem_up(int semNumber){
	if(semaphores[semNumber]->isValid == 0){
		return EINVAL;
	}

	// add resource to that specific semaphore number
	semaphores[semNumber]->value++; 

	if(queue_size(semaphores[semNumber]->q) > 0){ // if processes blocked on semaphore then remove process
		semaphores[semNumber]->value--;

		int source = dequeue(semaphores[semNumber]->q); // remove process from queue
		sendnb(source, &m); // reply to unblock the process

		// message m;
		// m.m_type = OK;
		// m.m_source = dequeue(semaphores[semNumber]->q); // remove process from queue
		// sendnb(m.m_source, &m);
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

