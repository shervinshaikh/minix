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
#include <stdlib.h>
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