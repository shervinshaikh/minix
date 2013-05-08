/* Function prototypes. */

/* semaphore.c */
int main(void);
int do_sem_init(message *m_ptr);
int do_sem_down(message *m_ptr);
int do_sem_up(message *m_ptr);
int do_sem_release(message *m_ptr);