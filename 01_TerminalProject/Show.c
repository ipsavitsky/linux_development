#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DX 7
#define DY 3

int main(int argc, char *argv[]) {
        WINDOW *frame, *win;
        int c = 0;
	char* filename = NULL;

	if (argc != 2) {
	  fprintf(stderr, "invalid amount of arguments (%d), expected 1\n", argc - 1);
	  exit(1);
	}

	if ((filename = argv[1]) == NULL) {
	  fprintf(stderr, "invalid filename\n");
	  exit(1);
	}

	FILE* infile = fopen(filename, "r");

	if (infile == NULL) {
	  fprintf(stderr, "error opening file\n");
	  exit(1);
	}

	char *lines[1024];

	size_t bufsize = 0;
	char* line = NULL;
	int a = 0;
	int cntr = 0;

	while((a = getline(&line, &bufsize, infile)) != -1) {
	  lines[cntr++] = strdup(line);

	  if(cntr >= 1024) {
	    fprintf(stderr, "too many lines\n");
	  }
	}

	free(line);
	fclose(infile);

        initscr();
        noecho();
        cbreak();
        printw("Showing: %s", filename);
        refresh();

        frame = newwin(LINES - 2*DY, COLS - 2*DX, DY, DX);
        box(frame, 0, 0);
        /* mvwaddstr(frame, 0, (int)((COLS - 2*DX - 5) / 2), "Border: "); */
        wrefresh(frame);


	int nlines = LINES - 2*DY - 2;
	int ncols = COLS - 2*DX - 2;
        win = newwin(nlines, ncols, DY+1, DX+1);
        keypad(win, TRUE);
        scrollok(win, TRUE);

	int offset = 0;
	do {
	  int print_length = (cntr < nlines) ? cntr : nlines;
	  for (int i = offset; i < print_length + offset; ++i) {
	    wprintw(win, "%s", lines[i]);
	  }

	  switch (c) {
	  case KEY_UP:
	    offset = offset <= 0 ? 0 : offset - 1;
	    break;
	  case KEY_DOWN:
	    offset = (nlines + offset) >= cntr ? offset : offset + 1;
	    break;
	  }
	} while ((c = wgetch(win)) != 27);

	for (int i = 0; i < cntr; ++i) {
	  free(lines[i]);
	}
	
        delwin(win);
        delwin(frame);
        endwin();
        return 0;
}
