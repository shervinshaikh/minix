#include <lib.h>
#include <unistd.h>


int semaphore()
{
  message m;
  _syscall(PM_PROC_NR, SEMAPHORE, &m);
}
