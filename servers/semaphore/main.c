#include <minix/keymap.h>
#include <minix/callnr.h>
#include <minix/com.h>
#include <minix/ds.h>
#include <minix/type.h>
#include <minix/endpoint.h>
#include <minix/minlib.h>
#include <minix/type.h>
#include <minix/vm.h>
#include <minix/crtso.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/utsname.h>
#include <string.h>
#include <machine/archtypes.h>
#include <env.h>

/*===========================================================================*
 *				do_semaphore				             *
 *===========================================================================*/
int p = 0;
int do_semaphore() {
  printf("p: %d\n", p++);
  printf("Adios motherfucker\n");
  return 0;
}