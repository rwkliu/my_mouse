#include "coord.h"
#ifndef HASH_TABLE_INCLUDE_H
#define HASH_TABLE_INCLUDE_H
typedef struct {
    coord *key;
    coord *value;
} ht_entry;

typedef struct ht {
    ht_entry *entries;
    int capacity;
    int length;
} ht;

ht *ht_create();
void ht_free(ht *table);

#endif