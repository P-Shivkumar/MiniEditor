myvim: main.o command.o 
	cc main.o command.o -lncurses -o myvim
main.o: main.c command.h main.h
	cc -Wall -c main.c
command.o: command.o main.h command.h
	cc -Wall -c command.c
