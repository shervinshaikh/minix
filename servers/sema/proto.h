/* struct prototypes */
struct Node;
struct Queue;
struct Semaphore;

/* Function prototypes. */

/* semaphore.c */
int main(void);
int do_sem_init(message *m_ptr);
int do_sem_down(message *m_ptr);
int do_sem_up(message *m_ptr);
int do_sem_release(message *m_ptr);

struct Queue* init_queue();
int dequeue(struct Queue* q);
void enqueue(struct Queue* q, int process);
int queue_size(struct Queue* q);
void clear_queue(struct Queue* q);