#include <stdlib.h>
#include "coord.h"

coord *coord_new(int row, int col) {
    coord *new_coord = malloc(sizeof(coord));
    new_coord->row = row;
    new_coord->col = col;
    new_coord->next = NULL;
    return new_coord;
}

void coord_free(coord *coord_s) {
    coord *coord_ptr = coord_s;
    coord *coord_to_delete = coord_s;

    while (coord_ptr) {
        coord_ptr = coord_ptr->next;
        free(coord_to_delete);
        coord_to_delete = coord_ptr;
    }
    free(coord_s);
}