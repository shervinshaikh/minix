#include <minix/callnr.h>
#include <minix/com.h>
#include <minix/config.h>
#include <minix/ipc.h>
#include <minix/endpoint.h>
#include <minix/sysutil.h>
#include <minix/const.h>
#include <minix/type.h>

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

// down = synchronous
void sem_down(endpoint_t e)
{
	message m;
	int r;

	m.m_type = SEM_DOWN;
	r = sendrec(e, &m);
	if (r)
		printf("semaphore down error\n");
}

// up not synchronous
void sem_up(endpoint_t e)
{
	message m;
	int r;

	m.m_type = SEM_UP;
	r = sendnb(e, &m);
	if (r)
		printf("semaphore up error\n");
}

int main(int argc, char *argv[])
{
	endpoint_t who;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <name> <endpoint>\n", argv[0]);
		return -1;
	}

	who = atoi(argv[2]);

	while (1) {
		/* take a fork */
		sem_down(who);
		/* take another fork */
		sem_down(who);

		printf("[%s] is eating...\n", argv[1]);
		sleep(5);

		/* put down two forks */
		sem_up(who);
		sem_up(who);

		/* the philosopher often thinks too hard
		 * and gets hungry easily, so he needs to
		 * eat again in a short time. :-)
		 */
		printf("[%s] is thinking...\n", argv[1]);
		sleep(15);
	}
	return 0;
}
