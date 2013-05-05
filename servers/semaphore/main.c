#include <minix/callnr.h>
#include <minix/crtso.h>
#include <stdio.h>

/*===========================================================================*
 *				do_semaphore				             *
 *===========================================================================*/
int p = 0;
int do_semaphore() {
  printf("p: %d\n", p++);
  printf("Adios motherfucker\n");
  return 0;
}