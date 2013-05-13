#ifndef SEM_H_
#define SEM_H_

struct Node;
struct Queue;
struct Semaphore;

/* Function prototypes */
int do_sem_init(int start_value);
int do_sem_down(int semNumber, int source);
int do_sem_up(int semNumber);
int do_sem_release(int semNumber);
struct Queue* init_queue();
int dequeue(struct Queue* q);
void enqueue(struct Queue* q, int process);
int queue_size(struct Queue* q);

#endif