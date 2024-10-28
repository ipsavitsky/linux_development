#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 1024

// in this program we assume that close() always works correctly when given the
// correct arguments (a descriptor that we know is open)

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Not enough parameters");
    exit(1);
  }

  char *in_filename = argv[1];
  char *out_filename = argv[2];

  int infile_fd, outfile_fd;
  if ((infile_fd = open(in_filename, O_RDONLY, 0)) == -1) {
    perror("open infile");
    exit(errno);
  }
  if ((outfile_fd = open(out_filename, O_WRONLY | O_CREAT | O_TRUNC, 0666)) ==
      -1) {
    perror("open outfile");
    close(infile_fd);
    exit(errno);
  }

  char buf[BUF_SIZE];
  int ret = 0;
  while ((ret = read(infile_fd, buf, BUF_SIZE))) {
    if (ret == -1) {
      perror("reading infile");
      close(infile_fd);
      close(outfile_fd);
      unlink(out_filename);
      exit(errno);
    }

    if (write(outfile_fd, buf, ret) == -1) {
      perror("writing outfile");
      close(infile_fd);
      close(outfile_fd);
      unlink(out_filename);
      exit(errno);
    }
  }

  close(infile_fd);
  close(outfile_fd);
  if (unlink(in_filename) == -1) {
    perror("unlink");
    exit(errno);
  }
  return 0;
}
