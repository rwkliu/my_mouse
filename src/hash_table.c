#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

ht *ht_create() {
    ht *table = malloc(sizeof(ht));
    if (table == NULL) {
        return NULL;
    }
    table->length = 0;
    table->entries = NULL;
    table->end = NULL;

    return table;
}

void ht_free(ht *table) {
    if (table == NULL) {
        return;
    }

    ht_entry *entry_ptr = table->entries;
    ht_entry *entry_to_delete = table->entries;

    while (entry_ptr) {
        entry_ptr = entry_ptr->next;
        free(entry_to_delete->key);
        free(entry_to_delete->value);
        free(entry_to_delete);
        entry_to_delete = entry_ptr;
    }
    free(table);
}

ht_entry *key_in_table(ht *table, coord *key) {
    ht_entry *entry_ptr = table->entries;

    while (entry_ptr) {
        if (entry_ptr->key->row == key->row && entry_ptr->key->col == key->col) {
            return entry_ptr;
        }
        entry_ptr = entry_ptr->next;
    }
    return NULL;
}

// Adds key-value coord struct pair to table if the key doesn't exist; otherwise
// change the existing value to the new value
ht *ht_set(ht *table, coord *key, coord *value) {
    if (value == NULL) {
        return NULL;
    }

    ht_entry *exist_entry = NULL;
    if ((exist_entry = key_in_table(table, key))) {
        free(key);
        free(exist_entry->value);
        exist_entry->value = value;
    } else {
        ht_entry *new_entry = malloc(sizeof(ht_entry));
        new_entry->key = key;
        new_entry->value = value;
        new_entry->next = NULL;

        if (table->end == NULL) {
            table->entries = new_entry;
            table->end = new_entry;
        } else {
            table->end->next = new_entry;
            table->end = new_entry;
        }
    }

    return table;
}

// Return the struct coord value associated with the key; otherwise return NULL
// and print error message to stderr
coord *ht_get(ht *table, coord *key) {
    if (key == NULL) {
        fprintf(stderr, "No key\n");
        return NULL;
    }

    ht_entry *exist_entry = NULL;
    if ((exist_entry = key_in_table(table, key))) {
        return exist_entry->value;
    } else {
        fprintf(stderr, "Key not found\n");
        return NULL;
    }
}

void ht_print(ht *table) {
    ht_entry *entry_ptr = table->entries;

    while (entry_ptr) {
        printf("key: %d, %d value: %d %d\n", entry_ptr->key->row, entry_ptr->key->col, entry_ptr->value->row, entry_ptr->value->col);
        entry_ptr = entry_ptr->next;
    }
}