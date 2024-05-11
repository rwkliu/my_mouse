#include <string.h>
#include <stdlib.h>
#include "maze.h"
#include "helpers.h"

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