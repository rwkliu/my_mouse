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

    if (validate_maze(maze_1) == 0) {
        fprintf(stderr, "MAP ERROR");
        return 1;
    }   else {
        solve_maze(maze_1);
    }

    return 0;
}