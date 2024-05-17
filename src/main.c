#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "helpers.h"
#include "maze.h"
#include "coord_array.h"
#include "queue.h"

#define NUM_DIRECTIONS 4

int main(int argc, char **argv) {
    int fd = open_file(argv[1]);
    if (fd == -1) {
        printf("Error reading file\n");
        return 1;
    }
    maze_s *maze_1 = initialize_maze(fd);
    coord_array *visited = coord_array_new();
    queue_t *queue = NULL;
    coord *current = NULL;


    int direction[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    queue = queue_enqueue(queue, maze_1->start_row, maze_1->start_col);
    coord_array_add(maze_1->start_row, maze_1->start_col, visited);

    printf("10x10* o12\n");
    print_maze(maze_1);
    printf("10 STEPS!\n");
    // printf("bfs finished\n");


    queue_free(queue);
    coord_array_free(visited);
    free_maze(maze_1);
    return 0;
}