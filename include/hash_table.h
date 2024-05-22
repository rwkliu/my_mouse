#include "coord.h"
#ifndef HASH_TABLE_INCLUDE_H
#define HASH_TABLE_INCLUDE_H
typedef struct entry {
    coord *key;
    coord *value;
    struct entry *next;
} ht_entry;

typedef struct ht {
    ht_entry *entries;
    ht_entry *end;
    int length;
} ht;

ht *ht_create();
void ht_free(ht *table);
ht *ht_set(ht *table, coord *key, coord *value);
coord *ht_get(ht *table, coord *key);
void ht_print(ht *table);
int ht_has_key(ht *table, coord *key);

#endif