#ifndef COORD_H
#define COORD_H

typedef struct s_coord {
    int row;
    int col;
    struct s_coord *next;
}   coord;

coord *coord_new(int row, int col);
void coord_free(coord *coord_s);

#endif