#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "helpers.h"

typedef struct s_maze {
  int row;
  int col;
  char *maze;
} maze;

int get_integer(char *int_string, int start, int end) {
  int num_digits = end - start;
  char *int_substring = calloc(num_digits + 1, sizeof(char));
  int_substring = strncpy(int_substring, int_string, num_digits);
  int result = my_atoi(int_substring);
  free(int_substring);
  return result;
}

int get_maze_size(char *maze_size_string) {
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

  return col;
}

int main(int argc, char **argv) {
  int fd = open_file(argv[1]);
  char *maze_size = read_one_line(fd);
  // printf("%s\n", maze_size);
  int row_end = get_maze_size(maze_size);
  printf("%d\n", row_end);
  return 0;
}