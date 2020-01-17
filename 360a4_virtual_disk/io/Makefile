all: File
	cd ../disk && $(MAKE)
	./File
File: File.o
	gcc -o File File.o
File.o: File.c
	gcc -c File.c -o File.o -Wall -Werror
clean:
	-rm -f *.o


