#include <unistd.h>
#include <stdio.h>

int main(){

sem_init(500);
printf("\n");

sem_up(5);
printf("\n");

//sem_down(27);
printf("\n");

//sem_release(18);
printf("\n");

return 0;

}
