
#include <queue.h>
#include <stdlib.h>

void init_queue(struct queue *queue) {
  queue->in = 0;
  queue->out = 0;
  queue->count = 0;
};

void *dequeue(struct queue *queue) {
  void *result;
  if (queue->count <= 0) {
    exit(1);
  }
  result = queue->array[queue->out];
  queue->out = (queue->out + 1) % QUEUE_LEN;
  queue->count--;
  return result;
};

void enqueue(struct queue *queue, void *entity) {
  if (queue->count >= QUEUE_LEN) {
    exit(1);
  }
  queue->array[queue->in] = entity;
  queue->in = (queue->in + 1) % QUEUE_LEN;
  queue->count++;
};


