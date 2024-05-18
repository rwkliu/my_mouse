#include <stdio.h>
#include <stdlib.h>
#include "node.h"

node *node_new(int row, int col, int distance, node *next, node *prev) {
    node *new_node = malloc(sizeof(node));
    new_node->row = row;
    new_node->col = col;
    new_node->distance = distance;
    new_node->next = next;
    new_node->prev = prev;
    return new_node;
}