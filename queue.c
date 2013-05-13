#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"


struct Node
{
	int process;
	struct Node* next;
};

int size = 0;
struct Node *rear = NULL, *front = NULL;

int dequeue(){
	struct Node *temp = front;
	if(temp == NULL){
		// queue empty, should never reach here
		return -1;
	}
	front = front->next;
	temp->next = NULL;
	size--;
	return temp->process;
}

void enqueue(int process){
	struct Node *var = (struct Node*)malloc(sizeof(struct Node));
	var->process = process;
	if(front == NULL){
		front = var;
		front->next = NULL;
		rear = front;
	}
	else{
		rear->next = var;
		rear = var;
		//front->next = NULL;
	}
	size++;
	printf("%d was added to the queue and the new size: %d\n", rear->process, size);
}


int queue_size(){
	return size;
}

// int main(){
// 	printf("about to add to queue\n");
// 	enqueue(1);
// 	enqueue(2);
// 	enqueue(3);
// 	printf("%d was removed from the queue\n", dequeue());
// 	printf("Current queue size: %d\n", queue_size());
// 	printf("%d was removed from the queue\n", dequeue());
// 	enqueue(4);
// 	printf("%d was removed from the queue\n", dequeue());
// 	printf("%d was removed from the queue\n", dequeue());
// 	return 0;
// }