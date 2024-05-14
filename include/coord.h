#ifndef COORD_H
#define COORD_H

typedef struct {
    int row;
    int col;
    coord *next;
}   coord;

coord *coord_new();
void coord_free(coord *coord_s);

#endif