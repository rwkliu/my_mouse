#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "coord.h"
#include "node.h"

queue_t *queue_new() {
  queue_t *queue = malloc(sizeof(queue_t));
  queue->head = NULL;
  return queue;
}

queue_t *queue_enqueue(queue_t *queue, int row, int col, int distance, node *prev_node) {
  node *node_ptr = queue->head;
  node *new_node = node_new(row, col, distance, NULL, prev_node);

  if (node_ptr == NULL) {
    queue->head = new_node;
    return queue;
  }

  while (node_ptr->next) {
    node_ptr = node_ptr->next;
  }

  node_ptr->next = new_node;
  return queue;
}

node *queue_dequeue(queue_t **queue) {
  if (*queue == NULL) {
    return NULL;
  }

  node *popped_node = (*queue)->head;
  (*queue)->head = (*queue)->head->next;
  return popped_node;
}

void queue_free(queue_t *queue) {
  node *node_to_delete = queue->head;

  while (node_to_delete) {
    queue->head = node_to_delete->next;
    if (node_to_delete->prev) {
      free(node_to_delete->prev);
    }
    free(node_to_delete);
    node_to_delete = queue->head;
  }
  free(queue);
}

void queue_print(queue_t *queue) {
  if (queue == NULL) {
    printf("queue is empty\n");
    return;
  }

  node *node_ptr = queue->head;
  while (node_ptr) {
    printf("row: %d, col: %d\n", node_ptr->row, node_ptr->col);
    node_ptr = node_ptr->next;
  }
}
