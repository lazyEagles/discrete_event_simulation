
#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_LEN 512

struct queue {
  void* array[QUEUE_LEN];
  int in;
  int out;
  int count;  
};

void init_queue(struct queue *queue);
void *dequeue(struct queue *queue);
void enqueue(struct queue *queue, void *entity); 
 
#endif
