#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main(){
//fork();
sem_init(2);
sem_init(1);
sem_init(2);
sem_down(0);
sem_down(2);
printf("grad is eating.....\n");
sem_up(0);
sem_up(2);
printf("grad finished eating\n");
//exit(0);

sem_release(0);
sem_release(1);
sem_release(2);
return 0;

}
