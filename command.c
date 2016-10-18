#include <ncurses.h>
#include <ctype.h>
#include <stdlib.h>
#include "command.h"
#include "main.h"
void printwinComm(WINDOW *winEdit, WINDOW *winComm) {
	int ey, ex;
	getyx(winEdit, ey, ex);
	wmove(winComm, 0, 0);
	wclrtobot(winComm);
	wrefresh(winComm);
	mvwprintw(winComm, 0, COLS - 20, "%d, %d", ey + 1, ex + 1);
	wrefresh(winComm);
	wmove(winEdit, ey, ex);	
}
void insert(WINDOW *winEdit, WINDOW *winComm, int *flag) {
	if(*flag == MODE_COMM) {
		*flag = MODE_EDIT;
	}
	if(*flag == MODE_EDIT) {
		int ch;
		while(isprint(ch = wgetch(winEdit))) {
			waddch(winEdit, ch);
			printwinComm(winEdit, winComm);
		}
	}
}
void yxlastChar(WINDOW *winEdit, int *y, int *x) {
	int ymax, xmax;
	int i, j;
	getmaxyx(winEdit, ymax, xmax);
	for(i = ymax - 1; i >= 0; i--) {
		for(j = xmax - 1; j >= 0; j--) {
			if(isspace(winch(winEdit))) {
				wmove(winEdit, i, j);
			}
			else {
				*y = i;
				*x = j;
				return;
			}
		}
	}
}
void savefile(WINDOW *winEdit,  WINDOW *winComm, FILE *fp, int *flag, int *ch, int *quit) {
	if(*flag != MODE_COMM)
		return;
	else { 
		int c, cha;
		int *y, *x;
		wrefresh(winComm);
		mvwprintw(winComm, 0, 0, "%c", *ch);
		wrefresh(winComm);
		while(isprint(c = wgetch(winComm)) && quit == 0) {
			switch (c) {
				int i, j;
				case 'w':
					mvwprintw(winComm, 0, 1, "w");
					wrefresh(winComm);
					yxlastChar(winEdit, y, x);
					wmove(winEdit, 0, 0);
					if(fp != NULL) {
						for(i = 0; i < *y; i++) {
							for(j = 0; j < COLS; j++) {
								cha = winch(winEdit);
								fputc(cha, fp);
							}
						}
						for(j = 0; j < *x; j++) {
							cha = winch(winEdit);
							fputc(cha, fp);
						}
					}
					break;
				case 'q':
					mvwprintw(winComm, 0, 1, "q");
					wclrtobot(winEdit);
					*quit = 1;
					break;
				default :
					break;
			}
		}
	}
}
