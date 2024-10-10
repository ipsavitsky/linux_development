#include <stdio.h>
#include <stdlib.h>

void print_range(int start, int stop, int step) {
  for (int i = start; i < stop; i += step) {
    printf("%d\n", i);
  }
}

int main(int argc, char *argv[]) {
  long from = 0, to = 0, increment = 0;
  switch (argc) {
  case 1:
    fprintf(stderr, "Not enough arguments\n");
    break;
  case 2:
    to = strtol(argv[1], NULL, 10);
    print_range(0, to, 1);
    break;
  case 3:
    from = strtol(argv[1], NULL, 10);
    to = strtol(argv[2], NULL, 10);
    print_range(from, to, 1);
    break;
  case 4:
    from = strtol(argv[1], NULL, 10);
    to = strtol(argv[2], NULL, 10);
    increment = strtol(argv[3], NULL, 10);
    print_range(from, to, increment);
    break;
  }
}
