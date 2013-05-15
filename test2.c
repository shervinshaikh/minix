#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main(){
printf("sem_down(0): %d\n", sem_down(0));
printf("sem_down(555): %d\n", sem_down(5));
return 0;

}
