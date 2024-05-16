#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "helpers.h"
#include "maze.h"
#include "coord_array.h"
#include "queue.h"

int main(int argc, char **argv) {
    int fd = open_file(argv[1]);
    if (fd == -1) {
        printf("Error reading file\n");
        return 1;
    }
    maze_s *maze_1 = initialize_maze(fd);
    coord_array *visited = coord_array_new();
    queue_t *queue = NULL;

    queue = queue_enqueue(queue, 0, 0);
    queue = queue_enqueue(queue, 1, 1);
    queue_print(queue);

    coord *de_coord = queue_dequeue(&queue);
    printf("popped row: %d, popped col: %d\n", de_coord->row, de_coord->col);
    coord_free(de_coord);
    queue_print(queue);

    queue_free(queue);
    coord_array_free(visited);
    free_maze(maze_1);
    return 0;
}