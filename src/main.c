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

    while (queue) {
        current = queue_dequeue(&queue);
        if (current->row == maze_1->end_row && current->col == maze_1->end_col) {
            printf("Path found to exit\n");
            coord_free(current);
            break;
        }

        for (int i = 0; i < NUM_DIRECTIONS; i++) {
            int next_cell_row = current->row + direction[i][0];
            int next_cell_col = current->col + direction[i][1];

            if (0 <= next_cell_row && \
                next_cell_row < strlen(*(maze_1->maze)) && \
                0 <= next_cell_col && \
                next_cell_col < strlen(maze_1->maze[0]) && \
                maze_1->maze[next_cell_row][next_cell_col] != '*' && \
                !coord_array_contains(next_cell_row, next_cell_col, visited)
                ) {
                    queue = queue_enqueue(queue, next_cell_row, next_cell_col);
                    coord_array_add(next_cell_row, next_cell_col, visited);
                }
        }
        coord_free(current);
    }
    printf("bfs finished\n");


    queue_free(queue);
    coord_array_free(visited);
    free_maze(maze_1);
    return 0;
}