#include <stdio.h>
#include <stdlib.h>


void UGrad(int mutex, int usem){
	int i = 0;
	while(i<20){ // change to run forever
		sem_down(mutex);

		if(fork() == 0){
			UGrad1(usem);
		}
		else{
			UGrad2(usem);
		}
		sem_down(mutex);
		i++;
	}
	return;
}

void UGrad1(int usem){
	sem_down(usem);
	printf("UGrad1 is eating...\n");
	sem_up(usem);
	return;
}

void UGrad2(int usem){
	sem_down(usem);
	printf("Ugrad2 is eating...\n");
	sem_up(usem);
	return;
}