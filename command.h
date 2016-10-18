#ifndef __COMMAND_H
#define __COMMAND_H

void printwinComm(WINDOW *winEdit, WINDOW *winComm);
void insert(WINDOW *winEdit, WINDOW *winComm, int *flag);
void yxlastChar(WINDOW *winEdit, int *y, int *x);
void savefile(WINDOW *winEdit,WINDOW *winComm, FILE *fp, int *flag, int *ch, int *quit);

#endif
