kapish: kapish.o
	gcc -o kapish kapish.o
kapish.o: kapish.c
	gcc -c kapish.c -o kapish.o -Wall -Werror
