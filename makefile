wordSearch2D: puzzle2D.o wordSearch2D.o
	gcc -Wall -std=c99 -o wordSearch2D puzzle2D.o wordSearch2D.o -lm

wordSearch2D.o: wordSearch2D.c puzzle2D.h
	gcc -Wall -std=c99 -c wordSearch2D.c -lm

puzzle2D.o: puzzle2D.c puzzle2D.h
	gcc -Wall -std=c99 -c puzzle2D.c -lm 

clean: 
	rm -f wordSearch2D *.o

