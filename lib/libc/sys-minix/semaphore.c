#include <lib.h>
#include <unistd.h>


void semaphore()
{
  message m;
  _syscall(PM_PROC_NR, SEMAPHORE, &m);
}