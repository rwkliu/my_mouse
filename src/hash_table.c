#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

#define INITIAL_CAPACITY 16
ht *ht_create() {
    ht *table = malloc(sizeof(ht));
    if (table == NULL) {
        return NULL;
    }
    table->length = 0;
    table->capacity = INITIAL_CAPACITY;

    table->entries = calloc(table->capacity, sizeof(ht_entry));
    if (table->entries == NULL) {
        free(table);
        return NULL;
    }
    return table;
}

void ht_free(ht *table) {
    for (int i = 0; i < table->capacity; i++) {
        free(table->entries[i].key);
    }
    free(table->entries);
    free(table);
}