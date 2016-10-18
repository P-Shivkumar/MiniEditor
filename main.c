#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <ncurses.h>
#include "command.h"
#include "main.h"
int main(int argc, char *argv[]) {
	FILE *fp;
	if(argc < 2) {
		printf("Usage :./myvim <soursefile>\n");
		return EINVAL;
	} 
	fp = fopen(argv[1], "r+");
	if(fp == NULL) {
		char create;
		printf("No file at given location. Create a new file?(y/n)");
		scanf("%c", &create);
		if(create  == 'Y' || create == 'y') {
			fp = fopen(argv[1], "w");
			fclose(fp);
		}
		if(fp == NULL) {
			perror("Open the file or create the file is failed !\n");
			return errno;
		}
	}
	if(fp != NULL) {
		int y, x, ymax, xmax, ylast, xlast;
		int flag = MODE_COMM;
		int quit = 0;
		int ch;
		WINDOW *winEdit, *winComm;
		initscr();
		cbreak();
		noecho();
		winEdit = derwin(stdscr, LINES - 1, COLS, 0, 0);
		winComm = derwin(stdscr, 1, COLS, LINES - 1, 0);
		scrollok(winEdit, TRUE);
		refresh();
		keypad(stdscr, TRUE);
		keypad(winEdit, TRUE);
		keypad(winComm, TRUE);
		while((ch = getc(fp)) != EOF) {
			waddch(winEdit, ch);
		}
		getyx(winEdit, ylast, xlast);
		wmove(winEdit, 0, 0);
		printwinComm(winEdit, winComm);
		while((ch = wgetch(winEdit)) != EOF && quit == 0) {
			switch(ch) {
				case KEY_UP :
					getyx(winEdit, y, x);
					wmove(winEdit, y - 1, x);
					printwinComm(winEdit, winComm);
					break;
				case KEY_DOWN:
					getyx(winEdit, y, x);
					wmove(winEdit, y + 1, x);
					printwinComm(winEdit, winComm);
					break;
				case KEY_LEFT:
					getyx(winEdit, y, x);
					wmove(winEdit, y, x - 1);
					printwinComm(winEdit, winComm);
					break;
				case KEY_RIGHT:
					getyx(winEdit, y, x);
					wmove(winEdit, y, x + 1);
					printwinComm(winEdit, winComm);
					break;
				case VK_ESCAPE:
					flag = MODE_COMM;
					printwinComm(winEdit, winComm);
					break;
				case 'i':
					insert(winEdit, winComm, &flag);
					printwinComm(winEdit, winComm);
					break;
				case VK_ENTER:
					break;
				case 's':
					savefile(winEdit, winComm, fp, &flag, &ch, &quit);
					printwinComm(winEdit, winComm);
					break;
			}
		}
		endwin();
		return 0;
	}
}
