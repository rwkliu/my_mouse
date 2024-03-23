#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../include/my_readline.h"

void print_file(int fd) {
  char *str = NULL;
  while((str = my_readline(fd)) != NULL) {
    printf("%s\n", str);
    free(str);
  }
}

int open_file(char *file) {
  int fd = open(file, O_RDONLY);
  if (fd == -1) {
    printf("file can't be opened\n");
    return -1;
  }
  return fd;
}

char *read_one_line(int fd) {
  return my_readline(fd);
}