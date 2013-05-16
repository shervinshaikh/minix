#include <stdio.h>
#include <stdlib.h>
#include "main.h"

void Grad(int mutex, int gsem){
	int i = 0;
	while(i<20){ // change to run forever
		sem_down(mutex);
		int k;
		for(k=0; k<=5; k++){
			fork();
			GradEat(gsem, k);
		}
		sem_up(mutex);	
		i++;
	}
	return;
}

void GradEat(int gsem, int k){
	sem_down(gsem);
	printf("Grad%d is eating...\n", k);
	sem_up(gsem);
	return;
}