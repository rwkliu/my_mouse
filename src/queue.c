#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

queue_t *queue_enqueue(queue_t *queue, void *x) {
  queue_t *queue_ptr = queue;
  queue_t *new_node = malloc(sizeof(queue_t));
  new_node->value = x;
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

void *queue_dequeue(queue_t **queue) {
  if (*queue == NULL) {
    return NULL;
  }

  queue_t *node_to_delete = *queue;
  void *dequeue_value = node_to_delete->value;
  *queue = (*queue)->next;
  free(node_to_delete);
  return dequeue_value;
}

void queue_free(queue_t *queue) {
  queue_t *queue_ptr = queue;
  queue_t *node_to_delete = queue;

  while (queue_ptr) {
    queue_ptr = queue_ptr->next;
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
    printf("%s\n", (char *)queue_ptr->value);
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
    queue_array[i] = queue->value;
    queue = queue->next;
  }
  queue_array[i] = NULL;
  return queue_array;
}