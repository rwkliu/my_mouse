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
    coord_array_add(0, 0, visited);
    coord_array_add(1, 1, visited);
    printf("%d\n", coord_array_contains(0,0,visited));
    printf("%d\n", coord_array_contains(1,0,visited));

    coord_array_free(visited);
    free_maze(maze_1);
    return 0;
}