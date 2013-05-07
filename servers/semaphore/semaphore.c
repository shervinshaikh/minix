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


#include "kernel/const.h"
#include "kernel/config.h"
#include "kernel/proc.h"

/*===========================================================================*
 *				main                                         *
 *===========================================================================*/

int main(void)
{

	printf("Semaphore service is now running..........\n");
	// because its defined in glo.h
	//message m;
	//endpoint_t who_e;
	int result;

	/* SEF local startup. */
	sef_startup();

	/* This is SEMAPHORE's main loop-  get work and do it, forever and forever. */
	while (TRUE) {
		int ipc_status;

		/* wait for request message */
		if ((result = sef_receive_status(ANY, &m, ipc_status)) != OK)
			printf("SEMAPHORE receive error %d\n", r);
		who_e = m.m_source;
		call_nr = m.m_type;

		printf("Call Number: %d", call_nr);
		printf("Who sent it: %d\n", who_e);

		result = (*call_vec[call_nr])();
	}

	/* impossible to get here */



	return 0;
}


void do_semaphore(void){
	printf("--------------- Inside do_semaphore function\n");
}
