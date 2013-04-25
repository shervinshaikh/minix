#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int main(){

	int pid = fork();
	int i;
	if(pid == 0){
		for(i=0; i<10000; i++){
			printf("CHILD: %d\n", i);
		}
	}
	else if(pid > 0){
		for(i=0; i<10000; i++){
			printf("PARENT: %d\n", i);
		}
	}
}
