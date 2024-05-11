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

maze_s *initialize_maze(int fd) {
    maze_s *maze_struct = malloc(sizeof(maze_s));
    char *first_line = read_one_line(fd);
    maze_struct = get_maze_size(first_line, maze_struct);
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

    free(first_line);
    return maze_struct;
}

void free_maze(maze_s *maze) {
    int i = 0;
    while (i < maze->row) {
        free(maze->maze[i]);
        i++;
    }
    free(maze->maze);
    free(maze);
}

void print_maze(maze_s *maze) {
    for (int i = 0; i < maze->row; i++) {
        printf("%s\n", maze->maze[i]);
    }
}