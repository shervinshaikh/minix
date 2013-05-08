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

#define DEBUG
#ifdef DEBUG
    #define    debug(f,...)    fprintf(stderr,f "",##__VA_ARGS__)
#else
    #define    debug(f,...)
#endif

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
			case SEM_INIT: result = do_sem_init(&m);
			case SEM_DOWN: result = do_sem_down(&m);
			case SEM_UP: result = do_sem_up(&m);
			case SEM_RELEASE: result = do_sem_release(&m);
		}

		setreply(who_e, result);
		sendreply();

		// Or do a switch statement and call the functions below??
		//result = (*call_vec[call_nr])();
	}

	/* impossible to get here */



	return 0;
}

int do_sem_init(message *m_ptr){
	debug("---------------  INIT");

	return OK;
}

int do_sem_down(message *m_ptr){
	debug("---------------  DOWN");

	return OK;
}

int do_sem_up(message *m_ptr){
	debug("---------------  UP");

	return OK;
}

int do_sem_release(message *m_ptr){
	debug("---------------  RELEASED");


	return OK;
}

