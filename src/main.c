#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "helpers.h"
#include "maze.h"

int main(int argc, char **argv) {
  int fd = open_file(argv[1]);
  if (fd == -1) {
    printf("Error reading file\n");
    return 1;
  }
  struct s_maze maze;
  char *maze_size_string = read_one_line(fd);
  get_maze_size(maze_size_string, &maze);
  free(maze_size_string);
  return 0;
}