all: taquin nqueens knights 

list.o: list.c list.h
	gcc -c list.c 

board.o: board.c board.h
	gcc -c board.c board.h -lm

nqueens: nqueens.c board.o list.o
	gcc -o nqueens nqueens.c board.o list.o -lm

knights: knights.c board.o list.o
	gcc -o knights knights.c board.o list.o -lm

taquin: taquin.c board.o list.o
	gcc -o taquin taquin.c board.o list.o -lm

clean: 
	rm -f nqueens knights taquin *.o