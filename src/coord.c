#include <stdlib.h>
#include "coord.h"

coord *coord_new() {
    coord *new_coord = malloc(sizeof(coord));
    new_coord->row = 0;
    new_coord->col = 0;
    new_coord->next = NULL;
    return new_coord;
}

void coord_free(coord *coord_s) {
    free(coord_s);
}