#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

int main(){
	int i;

	int mutex = sem_init(1);
	int gsem = sem_init(2);
	int usem = sem_init(2);

	Grad(mutex, gsem);
	// while(i<20){
		// if(fork() == 0){
		// 	Grad(mutex, gsem);
		// }
		// else{
		// 	UGrad(mutex, usem);
		// }
		// i++;
	// }

	sem_release(mutex);
	sem_release(gsem);
	sem_release(usem);
	return 0;
}




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
		sem_up(mutex);
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

void Grad(int mutex, int gsem){
	int i = 0;
	while(i<2){ // change to run forever
		sem_down(mutex);
		int k;
		printf("grabbed mutex\n");
		for(k=0; k<=5; k++){
			if(fork() == 0)
				GradEat(gsem, k);
		}
		sem_up(mutex);	
		printf("gave up mutex\n");
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