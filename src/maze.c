#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "maze.h"
#include "helpers.h"
#include "file.h"
#include "my_readline.h"
#include "queue.h"
#include "coord_array.h"

#define NUM_DIRECTIONS 4

int get_integer(char *int_string, int start, int end) {
  int num_digits = end - start;
  char *int_substring = calloc(num_digits + 1, sizeof(char));
  int_substring = strncpy(int_substring, int_string, num_digits);
  int result = my_atoi(int_substring);
  free(int_substring);
  return result;
}

maze_s *get_maze_size(char *maze_size_string, maze_s *maze_struct) {
  int row = 0;
  int col = 0;
  int start = 0;
  int end = 0;

  // Get rows and cols 
  for (int i = 0; i < strlen(maze_size_string); i++) {
    if (maze_size_string[i] == 'x') {
      row = get_integer(maze_size_string, start, end); 
      start = end + 1;
    }
    if (maze_size_string[i] == '*') {
      char *col_string = maze_size_string + start;
      col = get_integer(col_string, start, end);
    }
    end++;
  }

  maze_struct->row = row;
  maze_struct->col = col;

  return maze_struct;
}

maze_s *get_start_end(maze_s *maze) {
    char *top = maze->maze[0];
    char *bottom = maze->maze[maze->row - 1];
    int row_len = strlen(top);

    // Assign the start point
    for (int i = 0; i < row_len; i++) {
        if (top[i] == '1') {
            maze->start_row = 0;
            maze->start_col = i;
            break;
        }
    }
    // Assign the end point
    for (int i = 0; i < row_len; i++) {
        if (bottom[i] == '2') {
            maze->end_row = maze->row - 1;
            maze->end_col = i;
            break;
        }
    }
    return maze;
}

maze_s *initialize_maze(int fd) {
    maze_s *maze_struct = malloc(sizeof(maze_s));
    maze_struct->header = read_one_line(fd);
    maze_struct = get_maze_size(maze_struct->header, maze_struct);
    maze_struct->maze = malloc(maze_struct->row * sizeof(char *));

    char *row_string = NULL;
    int row = 0;
    int cols = maze_struct->col;
    while ((row_string = my_readline(fd)) != NULL) {
        maze_struct->maze[row] = malloc(cols + 1 * sizeof(char));
        strncpy(maze_struct->maze[row], row_string, cols);
        maze_struct->maze[row][cols] = '\0';
        free(row_string);
        row++;
    }
    maze_struct = get_start_end(maze_struct);

    return maze_struct;
}

void free_maze(maze_s *maze) {
    int i = 0;
    while (i < maze->row) {
        free(maze->maze[i]);
        i++;
    }
    free(maze->header);
    free(maze->maze);
    free(maze);
}

void print_maze(maze_s *maze) {
    for (int i = 0; i < maze->row; i++) {
        printf("%s\n", maze->maze[i]);
    }
}

int validate_maze(maze_s *maze) {
    int starts = 0;
    int ends = 0;

    for (int i = 0; i < maze->row; i++) {
        for (int j = 0; j < maze->col; j++) {
            if (maze->maze[i][j] == '1') {
                starts++;
            }   else if (maze->maze[i][j] == '2') {
                ends++;
            }
        }
    }
    if (starts != 1) {
        return 0;
    }
    if (ends != 1) {
        return 0;
    }

    for (int i = 0; i < maze->row; i++) {
        for (int j = 0; j < maze->col; j++) {
            if (maze->maze[i][j] == '\0' && \
                    maze->maze[i][j] != ' ' && \
                    maze->maze[i][j] != '1' && \
                    maze->maze[i][j] != '2'
            ) {
                return 0;
            }
        }
    }
    return 1;
}

void solve_maze(maze_s *maze) {
    coord_array *visited = coord_array_new();
    queue_t *queue = queue_new();
    node *current = NULL;
    node *end = NULL;
    int direction[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    queue = queue_enqueue(queue, maze->start_row, maze->start_col, 0, NULL);
    coord_array_add(maze->start_row, maze->start_col, visited);

    while (queue->head) {
        current = queue_dequeue(&queue);
        int curr_row = current->row;
        int curr_col = current->col;
        int curr_dist = current->distance;

        if (curr_row == maze->end_row && curr_col == maze->end_col) {
            printf("%s\n", maze->header);
            end = current;
            while (end != NULL) {
                int row = end->row;
                int col = end->col;

                if ((row != maze->start_row || col != maze->start_col) && (row != maze->end_row || col != maze->end_col)) {
                    maze->maze[end->row][end->col] = 'o';
                }
                end = end->prev;
            }
            print_maze(maze);
            printf("%d STEPS\n", curr_dist);
            free(current);
            break;
        }

        for (int i = 0; i < NUM_DIRECTIONS; i++) {
            int new_row = curr_row + direction[i][0];
            int new_col = curr_col + direction[i][1];

            if (0 <= new_row && \
                    new_row < maze->row && \
                    0 <= new_col && \
                    new_col < maze->col && \
                    maze->maze[new_row][new_col] != '*' && \
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
    free_maze(maze);
}