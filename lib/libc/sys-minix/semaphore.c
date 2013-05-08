#include <lib.h>
#include <unistd.h>
#include <minix/callnr.h>
#include <minix/ipc.h>
#include <minix/com.h>

int semaphore()
{
  message m;
  m.m_type = SEM_INIT;
  printf("_syscall(SEMA_PROC_NR:%d, SEM_INIT:%d, m.m_type:%d)\n", SEMA_PROC_NR, SEM_INIT, m.m_type);
  _syscall(SEMA_PROC_NR, m_type, &m);
  printf("complete semaphore _syscall\n");
  return 0;
}


int sem_init(int start_value){
	printf("--------------- calling Semaphore INIT\n");

	message m;
	m.m1_i1 = start_value;
	_syscall(SEMA_PROC_NR, SEM_INIT, &m);
}

int sem_down(int semaphore_number){
	printf("--------------- calling Semaphore DOWN\n");

	message m;
	m.m1_i2 = semaphore_number;
	_syscall(SEMA_PROC_NR, SEM_DOWN, &m);
	return OK;
}

int sem_up(int semaphore_number){
	printf("--------------- calling Semaphore UP\n");

	message m;
	m.m1_i2 = semaphore_number;
	_syscall(SEMA_PROC_NR, SEM_UP, &m);
	return OK;
}

int sem_release(int semaphore){
	printf("--------------- calling Semaphore RELEASED\n");

	message m;
	m.m1_i3 = semaphore;
	_syscall(SEMA_PROC_NR, SEM_RELEASE, &m);

	return OK;
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