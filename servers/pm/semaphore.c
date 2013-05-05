#include "pm.h"
#include <sys/wait.h>
#include <assert.h>
#include <minix/callnr.h>
#include <minix/com.h>
#include <minix/sched.h>
#include <minix/vm.h>
#include <sys/ptrace.h>
#include <sys/resource.h>
#include <signal.h>
#include "mproc.h"
#include "param.h"

int do_semaphore() {
	printf("Adios motherfucker\n");
	// message m;
	// int result;
	// /* Initialize the semaphore server. */
	// initialize();
	// /* Main loop of server. Get work and process it. */
	// while(TRUE) {
	// 	/* Block and wait until a request message arrives. */
	// 	ipc_receive(&m);
	// 	/* Caller is now blocked. Dispatch based on message type. */
	// 	switch(m.m_type) {
	// 		case UP: result = do_up(&m); break;
	// 		case DOWN: result = do_down(&m); break;
	// 		default: result = EINVAL;
	// 	}
	// 	/* Send the reply, unless the caller must be blocked. */
	// 	if (result != EDONTREPLY) {
	// 		m.m_type = result;
	// 		ipc_reply(m.m_source, &m);
	// 	}
	// }
}


// int do_down(message *m_ptr) {}
// // 	/* Resource available. Decrement semaphore and reply. */
// // 	if (s > 0) {
// // 		s = s – 1; /* take a resource */
// // 		return(OK); /* let the caller continue */
// // 	}
// // 	 Resource taken. Enqueue and block the caller. 
// // 	enqueue(m_ptr->m_source); /* add process to queue */
// // 	return(EDONTREPLY); /* do not reply in order to block the caller */
// // }
// int do_up(message *m_ptr) {}

// 	message m; /* place to construct reply message */
// 	/* Add resource, and return OK to let caller continue. */
// 	s = s + 1; /* add a resource */
// 	/* Check if there are processes blocked on the semaphore. */
// 	if (queue_size() > 0) {  are any processes blocked? 
// 		m.m_type = OK; 
// 		m.m_source = dequeue(); /* remove process from queue */
// 		s = s – 1; /* process takes a resource */
// 		ipc_reply(m.m_source, m); /* reply to unblock the process */
// 	}
// 	return(OK); /* let the caller continue */
// }