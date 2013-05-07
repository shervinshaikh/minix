#include <lib.h>
#include <unistd.h>

int semaphore()
{
  message m;
  _syscall(SEMA_PROC_NR, SEMAPHORE, &m);
}

// sem_init sem_up


// int mycall(a, b, c)
// int a, b, c;
// {
	// message m;
	//  You may pass a buffer pointer here if necessary,
	// using m.m1_p1 instead. You can learn from
	// /usr/src/lib/posix/_write.c 
	// m.m1_i1 = a;
	// m.m1_i2 = b;
	// m.m1_i3 = c;
	// return(_syscall(FS, MYCALL, &m)); 
// }