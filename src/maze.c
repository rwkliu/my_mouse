#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "maze.h"
#include "helpers.h"
#include "file.h"
#include "my_readline.h"

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