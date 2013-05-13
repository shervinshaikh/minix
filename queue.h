#ifndef QUEUE_H_
#define QUEUE_H_

struct Node;
struct Queue;

/* Function prototypes */
struct Queue* init_queue();
int dequeue(struct Queue* q);
void enqueue(struct Queue* q, int process);
int queue_size(struct Queue* q);

#endif