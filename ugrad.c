#include <stdio.h>
#include <stdlib.h>
#include "main.h"

void UGrad(int mutex, int usem){
	while(1){
		sem_down(mutex);
		if(fork() == 0){
			UGrad1(usem);
		}
		else{
			UGrad2(usem);
		}
		sem_up(mutex);
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