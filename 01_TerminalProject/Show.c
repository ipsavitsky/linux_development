#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DX 7
#define DY 3

void print_file_lines(WINDOW *win, int screen_lines, char **lines,
                      int file_lines, int offset) {
  int print_length = (file_lines < screen_lines) ? file_lines : screen_lines;
  for (int i = offset; i < print_length + offset; ++i) {
    wprintw(win, "%s", lines[i]);
  }
}

int main(int argc, char *argv[]) {
  WINDOW *frame, *win;
  int c = 0;
  char *filename = NULL;

  if (argc != 2) {
    fprintf(stderr, "invalid amount of arguments (%d), expected 1\n", argc - 1);
    exit(1);
  }

  if ((filename = argv[1]) == NULL) {
    fprintf(stderr, "invalid filename\n");
    exit(1);
  }

  FILE *infile = fopen(filename, "r");

  if (infile == NULL) {
    fprintf(stderr, "error opening file\n");
    exit(1);
  }

  int line_buffer_size = 4;
  char **lines = (char **)malloc(line_buffer_size * sizeof(char *));
  size_t bufsize = 0;
  char *line = NULL;
  int input_line_count = 0;

  while (getline(&line, &bufsize, infile) != -1) {
    lines[input_line_count++] = strdup(line);

    if (input_line_count >= line_buffer_size) {
      fprintf(stderr, "extending buffer %d -> %d\n", line_buffer_size,
              line_buffer_size * 2);
      line_buffer_size *= 2;
      lines = (char **)realloc((void *)lines,
                               (line_buffer_size * 2) * sizeof(char *));
    }
  }

  free(line);
  fclose(infile);

  initscr();
  noecho();
  cbreak();
  printw("Showing: %s", filename);
  refresh();

  frame = newwin(LINES - 2 * DY, COLS - 2 * DX, DY, DX);
  box(frame, 0, 0);
  wrefresh(frame);

  int nlines = LINES - 2 * DY - 2;
  int ncols = COLS - 2 * DX - 2;
  win = newwin(nlines, ncols, DY + 1, DX + 1);
  keypad(win, TRUE);
  scrollok(win, TRUE);

  int offset = 0;

  print_file_lines(win, nlines, lines, input_line_count, offset);

  while ((c = wgetch(win)) != 27) {

    switch (c) {
    case KEY_UP:
      offset = offset <= 0 ? 0 : offset - 1;
      break;
    case KEY_DOWN:
      offset = (nlines + offset) >= input_line_count ? offset : offset + 1;
      break;
    }

    print_file_lines(win, nlines, lines, input_line_count, offset);
  }

  for (int i = 0; i < input_line_count; ++i) {
    free(lines[i]);
  }

  free(lines);

  delwin(win);
  delwin(frame);
  endwin();
  return 0;
}
