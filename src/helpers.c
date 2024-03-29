int my_atoi(char *num_string) {
  int integer = 0;
  int sign = 1;
  int int_len = strlen(num_string) - 1;

  while(*num_string) {
    if(*num_string == '-') {
      sign *= -1;
      num_string++;
      int_len--;
    }
    else {
      integer += (*num_string - '0') * my_recursive_pow(10, int_len);
      num_string++;
      int_len--;
    }
  }
  return integer * sign;
}