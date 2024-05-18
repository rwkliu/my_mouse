#ifndef NODE_INCLUDE_H
#define NODE_INCLUDE_H
typedef struct node_t {
    int row;
    int col;
    int distance;
    struct node_t *next;
    struct node_t *prev;
}   node;
node *node_new(int row, int col, int distance, node *next, node *prev);
#endif