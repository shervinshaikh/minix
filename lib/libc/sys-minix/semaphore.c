#include <lib.h>
#include <unistd.h>
#include <minix/callnr.h>
#include <minix/ipc.h>
#include <minix/com.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG
#ifdef DEBUG
    #define    debug(f,...)    fprintf(stderr,f "",##__VA_ARGS__)
#else
    #define    debug(f,...)
#endif

#define OK 0

// int semaphore()
// {
//   message m;
//   m.m_type = SEM_INIT;
//   debug("_syscall(SEMA_PROC_NR:%d, SEM_INIT:%d, m.m_type:%d)", SEMA_PROC_NR, SEM_INIT, m.m_type);
//   _syscall(SEMA_PROC_NR, m_type, &m);
//   debug("complete semaphore _syscall");
//   return 0;
// }


int sem_init(int start_value){
	debug("--------------- calling Semaphore INIT");

	message m;
	m.m_type = SEM_INIT;
	m.m1_i1 = start_value;
	debug("Start value: %d", m.m1_i1);
	debug("_syscall(SEMA_PROC_NR:%d, SEM_INIT:%d, m.m_type:%d)", SEMA_PROC_NR, SEM_INIT, m.m_type);
	_syscall(SEMA_PROC_NR, SEM_INIT, &m));
	return 1; // next available semaphore value
}

int sem_down(int semaphore_number){
	debug("--------------- calling Semaphore DOWN");

	message m;
	m.m_type = SEM_DOWN;
	m.m1_i2 = semaphore_number;
	debug("Semaphore number: %d", m.m1_i2);
	debug("_syscall(SEMA_PROC_NR:%d, SEM_DOWN:%d, m.m_type:%d)", SEMA_PROC_NR, SEM_DOWN, m.m_type);
	_syscall(SEMA_PROC_NR, SEM_DOWN, &m);
	return OK;
}

int sem_up(int semaphore_number){
	debug("--------------- calling Semaphore UP");

	message m;
	m.m_type = SEM_UP;
	m.m1_i2 = semaphore_number;
	debug("Semaphore number: %d", m.m1_i2);
	debug("_syscall(SEMA_PROC_NR:%d, SEM_UP:%d, m.m_type:%d)", SEMA_PROC_NR, SEM_UP, m.m_type);
	_syscall(SEMA_PROC_NR, SEM_UP, &m);
	return OK;
}

int sem_release(int semaphore){
	debug("--------------- calling Semaphore RELEASED");

	message m;
	m.m_type = SEM_RELEASE;
	m.m1_i3 = semaphore;
	debug("Semaphore: %d", m.m1_i3);
	debug("_syscall(SEMA_PROC_NR:%d, SEM_RELEASE:%d, m.m_type:%d)", SEMA_PROC_NR, SEM_RELEASE, m.m_type);
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