#include "node.h"
#ifndef QUEUE_INCLUDE_H
#define QUEUE_INCLUDE_H
typedef struct queue_t {
    node *head;
} queue_t;
queue_t *queue_new();
queue_t *queue_enqueue(queue_t *queue, int row, int col, int distance, node *prev_node);
node *queue_dequeue(queue_t **queue);
void queue_free(queue_t *queue);
void queue_print(queue_t *queue);
#endif