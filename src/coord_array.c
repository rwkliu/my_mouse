#include <stdio.h>
#include <stdlib.h>
#include "coord_array.h"

coord_array *coord_array_new() {
    coord_array *coords = malloc(sizeof(coord_array));
    coords->size = 0;
    coords->coord_list = NULL;
    return coords;
}

void coord_array_free(coord_array *coords) {
    coord_free(coords->coord_list);
    free(coords);
}

coord_array *coord_array_add(int new_row, int new_col, coord_array *coords) {
    coord *new_coord = coord_new(new_row, new_col);
    coord *coord_ptr = coords->coord_list;
    coords->coord_list = new_coord;
    new_coord->next = coord_ptr;
    return coords;
}

int coord_array_contains(int row, int col, coord_array *coords) {
    return 1;
}
