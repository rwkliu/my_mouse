#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "coord.h"

queue_t *queue_enqueue(queue_t *queue, int row, int col) {
  queue_t *queue_ptr = queue;
  queue_t *new_node = malloc(sizeof(queue_t));
  new_node->coords = coord_new(row, col);
  new_node->next = NULL;

  if (queue == NULL) {
    return new_node;
  }

  while (queue_ptr->next) {
    queue_ptr = queue_ptr->next;
  }

  queue_ptr->next = new_node;
  return queue;
}

coord *queue_dequeue(queue_t **queue) {
  if (*queue == NULL) {
    return NULL;
  }

  queue_t *node_to_delete = *queue;
  coord *dequeue_value = node_to_delete->coords;
  *queue = (*queue)->next;
  free(node_to_delete);
  return dequeue_value;
}

void queue_free(queue_t *queue) {
  queue_t *queue_ptr = queue;
  queue_t *node_to_delete = queue;

  while (queue_ptr) {
    queue_ptr = queue_ptr->next;
    coord_free(node_to_delete->coords);
    free(node_to_delete);
    node_to_delete = queue_ptr;
  }
}

void queue_print(queue_t *queue) {
  if (queue == NULL) {
    printf("queue is empty\n");
    return;
  }

  queue_t *queue_ptr = queue;
  while (queue_ptr) {
    printf("row: %d, col: %d\n", queue_ptr->coords->row, queue_ptr->coords->col);
    queue_ptr = queue_ptr->next;
  }
}

int queue_length(queue_t *queue) {
  queue_t *queue_ptr = queue;
  int n = 0;

  while (queue_ptr) {
    n++;
    queue_ptr = queue_ptr->next;
  }
  return n;
}

void **queue_toArray(queue_t *queue) {
  int length_of_queue = queue_length(queue);
  void **queue_array = malloc((length_of_queue + 1) * sizeof(*queue_array));
  int i;

  for (i = 0; i < length_of_queue; i++) {
    queue_array[i] = queue->coords;
    queue = queue->next;
  }
  queue_array[i] = NULL;
  return queue_array;
}