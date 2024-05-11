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
  maze_s *maze_1 = initialize_maze(fd);
  printf("rows: %d\n", maze_1->row);
  printf("cols: %d\n", maze_1->col);
  print_maze(maze_1);

  free_maze(maze_1);
  return 0;
}