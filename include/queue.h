#include "coord.h"
#ifndef QUEUE_INCLUDE_H
#define QUEUE_INCLUDE_H
typedef struct queue_t {
  struct queue_t *next;
  coord *coords;
} queue_t;
queue_t *queue_enqueue(queue_t *queue, int row, int col);
coord *queue_dequeue(queue_t **queue);
void queue_free(queue_t *queue);
void queue_print(queue_t *queue);
void **queue_toArray(queue_t *queue);
#endif