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
// #include <minix/callnr.h>
// #include <minix/com.h>
#include <minix/ds.h>
//#include <minix/type.h>
// #include <minix/endpoint.h>
#include <minix/minlib.h>
// #include <minix/type.h>
#include <minix/vm.h>
#include <minix/crtso.h>
#include <signal.h>
// #include <stdlib.h>
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

/* Here is the data structure for a semaphore:
 *   - a counter indicating the current status of the semaphore.
 *   - a list of processes waiting on this semaphore, once a process
 *     issues an UP action and the semaphore is availabe, one process
 *     should be awaken from this list.
 */
struct semaphore {
	int counter;
	endpoint_t list[NR_PROCS];
	int list_nr;
};

struct semaphore sem;

/*===========================================================================*
 *				main                                         *
 *===========================================================================*/

int main(int argc, char *argv[])
{
	message m;
	endpoint_t who_e;
	int call_type, ipc_status;

	/* SEF local startup. */
	sef_local_startup();

	/* initialization */
	sem.counter = 1;
	// if (argc == 2)
	// 	sem.counter = atoi(argv[1]);
	/* ensure that the counter is at least one */
	// if (sem.counter == 0)
	// 	sem.counter = 1;
	sem.list_nr = 0;
	srandom(time(NULL));

	/* This is SEMAPHORE's main loop-  get work and do it, forever and forever. */
	while (TRUE) {
		int r;

		/* wait for request message */
		if ((r = sef_receive_status(ANY, &m, ipc_status)) != OK)
			printf("SEM receive error %d\n", r);
		who_e = m.m_source;
		call_type = m.m_type;

		if (call_type == SEM_DOWN) {
			/* process wants to acquire the semaphore */
			if (--sem.counter >= 0) {
				m.m_type = SEM_DOWN_OK;
				if ((r = sendnb(who_e, &m)) != OK)
					printf("SEM: unable to send reply to %d: %d\n",
						who_e, r);
			} else {
				/* add the process to the waiting list */
				if (sem.list_nr >= NR_PROCS)
					printf("SEM: too many processes: %d\n", sem.list_nr);
				else
					sem.list[sem.list_nr++] = who_e;
			}
		} else if (call_type == SEM_UP) {
			/* process relinquishes the semaphore */
			sem.counter++;
			if (sem.counter <= 0) {
				/* choose one process from the waiting list
				 * and unblock it.
				 */
				m.m_type = SEM_DOWN_OK;
				if (sem.list_nr == 0) {
					printf("SEM: inconsistent semaphore\n");
					continue;
				} else {
					/* the lucky one is based on "luck" ... */
					int p = random() % sem.list_nr;
					who_e = sem.list[p];

					--sem.list_nr;
					if (sem.list_nr != p) {
						/* exchange it */
						endpoint_t t = sem.list[p];
						sem.list[p] = sem.list[sem.list_nr];
						sem.list[sem.list_nr] = t;
					}
					if ((r = sendnb(who_e, &m)) != OK)
						printf("SEM: unable to send reply to %d: %d\n",
								who_e, r);
				}
			}
		} else {
			/* ignore. do not try to reply. */
			printf("SEM: invalid request %d from endpoint %d\n",
				call_type, who_e);
			continue;
		}
	}
	/* no way to get here */
	return -1;
}
