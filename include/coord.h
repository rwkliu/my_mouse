#ifndef COORD_H
#define COORD_H

typedef struct {
    int row;
    int col;
    coord *next;
}   coord;

coord *coord_new(int row, int col);
void coord_free(coord *coord_s);

#endif