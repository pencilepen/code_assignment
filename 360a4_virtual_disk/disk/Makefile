vdisk: disk
	./disk
disk: disk.o
	gcc -o disk disk.o
disk.o: disk.c
	gcc -c disk.c -o disk.o -Wall -Werror
clean:
	-rm -f *.o


