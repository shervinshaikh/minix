#include <sys/cdefs.h>
#include "namespace.h"
#include <lib.h>

#include <unistd.h>

#ifdef __weak_alias
__weak_alias(semaphore, semaphore)
#endif

void semaphore()
{
  message m;

  _syscall(PM_PROC_NR, SEMAPHORE, &m);
}