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
    free(coord_s);
}