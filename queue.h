#ifndef QUEUE_H_
#define QUEUE_H_

/* Function prototypes */

int dequeue();
void enqueue(int process);
int queue_size();

extern int size;
extern struct Node *rear, *front;

#endif