#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define RESULT_SIZE 100000

int READLINE_READ_SIZE = 100;
char *readline = NULL;

char *calloc_string(int size) {
  char *new_calloc_string = malloc(size * sizeof(char));

  for(int i = 0; i < size; i++) {
    new_calloc_string[i] = '\0';
  }
  
  return new_calloc_string;
}

void init_my_readline() {
  if(readline != NULL) {
    free(readline);
  }
  readline = calloc_string(READLINE_READ_SIZE + 1);
}

int my_string_index(char* param_1, char param_2){
  int index = 0;

  while (*param_1) {
    if(*param_1 == param_2) {
        return index;
    }
    index++;
    param_1++;
  }
  return -1;
}

//Return a pointer to the second string in str 
char *find_second_string(char *str) {
  int index = 0;

  if((index = my_string_index(str, '\n')) != -1) {
    str += index + 1;
  }
  return str;
}

//Allocate more memory to readline
void extend_readline() {
  char *temp = calloc_string(strlen(readline) + 1 + READLINE_READ_SIZE);
  strncpy(temp, readline, strlen(readline));
  free(readline);
  readline = temp;
}

char *my_readline(int fd) {
  int read_status = 1;
  char *result_string = NULL;
  int ln_index = -1;
  int readline_index = 0;

  result_string = calloc_string(RESULT_SIZE);

  //If readline != NULL, copy all text except first string into result
  //Then free and malloc readline
  if(readline != NULL) {
    result_string = strcpy(result_string, find_second_string(readline));
  }
  init_my_readline();

  //Copy result string into readline
  if(strlen(result_string) > 0) {
    if(strlen(readline) < strlen(result_string)) {
      free(readline);
      readline = calloc_string(strlen(result_string) + 1);
    }
    strncpy(readline, result_string, strlen(result_string));
  }

  while(read_status > 0) {
    read_status = read(fd, &readline[readline_index], READLINE_READ_SIZE);
    if(read_status > 0) {
      extend_readline();
      readline_index += READLINE_READ_SIZE;
    }
  }

  //Find the index of the first newline character
  ln_index = my_string_index(readline, '\n');
  if(ln_index == -1) {
    free(result_string);
    return NULL;
  }

  //Copy to result_string until newline is reached
  strncpy(result_string, readline, ln_index);
  result_string[ln_index] = '\0';

  return result_string;
}
