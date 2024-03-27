#include <stdio.h>
#include <stdlib.h>
#include "file.h"

int main(int argc, char **argv) {
  int fd = open_file(argv[1]);
  char *maze_size = read_one_line(fd);
  printf("%s\n", maze_size);
  return 0;
}