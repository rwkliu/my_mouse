#ifndef FILE_INCLUDE_H
#define FILE_INCLUDE_H

void print_file(int fd);
int open_file(char *file);
char *read_one_line(int fd);

#endif