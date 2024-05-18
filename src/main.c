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
    queue_t *queue = queue_new();
    node *current = NULL;
    node *end = NULL;


    int direction[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    queue = queue_enqueue(queue, maze_1->start_row, maze_1->start_col, 0, NULL);
    coord_array_add(maze_1->start_row, maze_1->start_col, visited);

    while (queue->head) {
        current = queue_dequeue(&queue);
        int curr_row = current->row;
        int curr_col = current->col;
        int curr_dist = current->distance;

        if (curr_row == maze_1->end_row && curr_col == maze_1->end_col) {
            printf("%s\n", maze_1->header);
            end = current;
            while (end != NULL) {
                int row = end->row;
                int col = end->col;

                if ((row != maze_1->start_row || col != maze_1->start_col) && (row != maze_1->end_row || col != maze_1->end_col)) {
                    maze_1->maze[end->row][end->col] = 'o';
                }
                end = end->prev;
            }
            // return curr_dist - 1;
            print_maze(maze_1);
            printf("%d STEPS\n", curr_dist);
            free(current);
            break;
        }

        for (int i = 0; i < NUM_DIRECTIONS; i++) {
            int new_row = curr_row + direction[i][0];
            int new_col = curr_col + direction[i][1];

            if (0 <= new_row && \
                    new_row < maze_1->row && \
                    0 <= new_col && \
                    new_col < maze_1->col && \
                    maze_1->maze[new_row][new_col] != '*' && \
                    !coord_array_contains(new_row, new_col, visited)
            ) {
                node *new_current = node_new(curr_row, curr_col, curr_dist, current->next, current->prev);
                queue = queue_enqueue(queue, new_row, new_col, curr_dist + 1, new_current);
                coord_array_add(new_row, new_col, visited);
            }
        }
        free(current);
    }
    queue_free(queue);
    coord_array_free(visited);
    free_maze(maze_1);
    return 0;
}