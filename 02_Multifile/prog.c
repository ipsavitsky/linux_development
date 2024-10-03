#include "outlib.h"
#include <stdio.h>
int main(int argc, char *argv[]) {
  int i;
  if ((Count = argc) > 1) {
    output("<INIT>");
    for (i = 1; i < argc; i++)
      output(argv[i]);
    output("<DONE>");
  } else {
    /* usage(argv[0]); */
    // hack for argv[0]
    usage("./prog");
  }

  return 0;
}
