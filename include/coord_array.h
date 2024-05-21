#include "coord.h"

#ifndef COORD_ARRAY_H
#define COORD_ARRAY_H

typedef struct {
    int size;
    coord *coord_list;
}   coord_array;

coord_array *coord_array_new();
void coord_array_free(coord_array *coords);
coord_array *coord_array_add(int new_row, int new_col, coord_array *coords);
int coord_array_contains(int row, int col, coord_array *coords);
void coord_array_print_coords(coord_array *coords);

#endif