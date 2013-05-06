#include <lib.h>
#include <unistd.h>

int semaphore()
{
  message m;
  _syscall(SEMA_PROC_NR, SEMAPHORE, &m);
}

// sem_init sem_up