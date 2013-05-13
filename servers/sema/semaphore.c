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
#include "queue.h"

#define DEBUG
#ifdef DEBUG
    #define    debug(f,...)    fprintf(stderr,f "\n",##__VA_ARGS__)
#else
    #define    debug(f,...)
#endif

int s = 1, nextValue = 0;

struct Semaphore
{
	// 0 = is NOT initialized, 1 = is initialized
	int isValid;
	struct Queue *q;
}

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

	int k;

	// initalize semaphores
	struct Semaphore semaphores[20];
	for(k=0; k<20; k++){
		semaphores[k] = (struct Semaphore*) malloc(sizeof(Semaphore));
		semaphores[k]->q = init_queue();
		semaphores[k]->isValid = 0;
	}

	/* This is SEMAPHORE's main loop-  get work and do it, forever and forever. */
	while (TRUE) {
		int ipc_status;

		debug("IN THE WHILE STATE FOR SEMA");

		/* wait for request message */
		//if ((result = sef_receive_status(ANY, &m, &ipc_status)) != OK)
		if ((result = receive(ANY, &m, &ipc_status)) != OK)
			debug("SEMAPHORE receive error %d", result);
		
		debug("SEMAPHORE recieved a message");

		who_e = m.m_source;
		call_nr = m.m_type;

		debug("Call Number: %d", call_nr);
		debug("Who: %d", who_e);

		
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
	debug("---------------  INIT");
	debug("server, Start value: %d", start_value);

	if(semaphore == NULL){
		return ENOMEM;
	}
	semaphore[nextValue] = m_ptr->m1_i1;

	return nextValue++;
}

int do_sem_down(message *m_ptr){
	int semNumber = m_ptr->m1_i2;
	debug("---------------  DOWN");
	debug("server, Semaphore number: %d", semNumber);
	if(semaphore[semNumber] == -2){
		return EINVAL;
	}
	if(semaphore[semNumber] > 0){ // available semaphore then decresase
		semNumber[semNumber]--;	
		return OK;
	}

	// add it to the queue and return not reply 
	
	return EDONTREPLY;
}

int do_sem_up(message *m_ptr){
	int semNumber = m_ptr->m1_i2;
	debug("---------------  UP");
	debug("server, Semaphore number: %d", semNumber);

	if(semaphore[semNumber] == -2){
		return EINVAL;
	}

	message m;
	s++; // add resource to that specific semaphore number

	if(0){ // if processes blocked on semaphore then remove process
		s--;
		m.m_type = OK;
		m.m_source = s; // remove process from queue
		sendnb(m_ptr->m_source, &m);
	}

	return OK;
}

int do_sem_release(message *m_ptr){
	int semNumber = m_ptr->m1_i3;
	debug("---------------  RELEASED");
	debug("server, Semaphore: %d", semNumber);

	// set isValid to 0, and NULL all pointers


	return OK;
}

