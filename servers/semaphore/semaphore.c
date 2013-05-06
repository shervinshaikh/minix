// #include <minix/keymap.h>
// #include <minix/callnr.h>
// #include <minix/com.h>
// #include <minix/ds.h>
// #include <minix/type.h>
// #include <minix/endpoint.h>
// #include <minix/minlib.h>
// #include <minix/type.h>
// #include <minix/vm.h>
// #include <minix/crtso.h>
// #include <signal.h>
// #include <stdlib.h>
// #include <fcntl.h>
// #include <sys/resource.h>
// #include <sys/utsname.h>
// #include <string.h>
// #include <machine/archtypes.h>
// #include <env.h>
// #include <stdio.h>
// sef_startup
/*===========================================================================*
 *				do_semaphore				             *
 *===========================================================================*/
// int p = 0;
// int main() {
//   printf("p: %d\n", p++);
//   printf("2.0 Adios motherfucker 2.0\n");
//   return 0;
// }



#define _SYSTEM	1
#define _MINIX 1

#include <minix/keymap.h>
#include <minix/ds.h>
#include <minix/minlib.h>
#include <minix/vm.h>
#include <minix/crtso.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/utsname.h>
#include <string.h>
#include <machine/archtypes.h>
#include <env.h>

#include <minix/callnr.h>
#include <minix/com.h>
#include <minix/config.h>
#include <minix/ipc.h>
#include <minix/endpoint.h>
#include <minix/sysutil.h>
#include <minix/const.h>
#include <minix/type.h>

#include <sys/types.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/*===========================================================================*
 *				main                                         *
 *===========================================================================*/

int main(void)
{
	message m;
	endpoint_t who_e;
	int call_type, ipc_status;

	/* SEF local startup. */
	sef_startup();

	/* This is SEMAPHORE's main loop-  get work and do it, forever and forever. */
	while (TRUE) {
		int r;

		/* wait for request message */
		if ((r = sef_receive_status(ANY, &m, ipc_status)) != OK)
			printf("SEMAPHORE receive error %d\n", r);
		who_e = m.m_source;
		call_type = m.m_type;

		printf("Call Type: %d", call_type);
		printf("Who sent it: %d\n", who_e);
	}

	/* impossible to get here */
	return -1;
}
