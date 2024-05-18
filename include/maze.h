#ifndef MAZE_INCLUDE_H
#define MAZE_INCLUDE_H

typedef struct s_maze {
  int row;
  int col;
  int start_row;
  int start_col;
  int end_row;
  int end_col;
  char *header;
  char **maze;
} maze_s;

int get_integer(char *int_string, int start, int end);
maze_s *get_maze_size(char *maze_size_string, maze_s *maze_struct);
maze_s *initialize_maze(int fd);
void print_maze(maze_s *maze);
void free_maze(maze_s *maze);

#endif