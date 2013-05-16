#include <stdio.h>
#include <stdlib.h>


void Grad(int mutex, int gsem){
	int i = 0;
	while(i<20){ // change to run forever
		sem_down(mutex);
		int k;
		for(k=0; k<=5; k++){
			fork();
			GradEat(gsem, k);
		}
		sem_down(mutex);	
		i++;
	}
	return;
}

void GradEat(int gsem, int k){
	sem_down(gsem);
	printf("Grad%d is eating...", k);
	sem_up(gsem);
	return;
}