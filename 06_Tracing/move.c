#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 1024

#define SAFE(call)                                                             \
  if ((call) == -1) {                                                          \
    fprintf(stderr, "%s\n", strerror(errno));                                  \
    close(infile_fd);                                                          \
    close(outfile_fd);                                                         \
    exit(errno);                                                               \
  }

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Not enough parameters");
    exit(1);
  }

  char *in_filename = argv[1];
  char *out_filename = argv[2];

  int infile_fd, outfile_fd;
  SAFE(infile_fd = open(in_filename, O_RDONLY, 0));
  SAFE(outfile_fd = open(out_filename, O_WRONLY | O_CREAT | O_TRUNC, 0666));

  char buf[BUF_SIZE];
  int ret = 0;
  while ((ret = read(infile_fd, buf, BUF_SIZE))) {
    if (ret == -1) {
      fprintf(stderr, "%s", strerror(errno));
      exit(errno);
    }
    SAFE(write(outfile_fd, buf, ret));
  }

  SAFE(close(infile_fd));
  SAFE(close(outfile_fd));
  SAFE(unlink(in_filename));
  return 0;
}
