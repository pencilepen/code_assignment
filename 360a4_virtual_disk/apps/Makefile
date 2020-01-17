#This Makefile will run disk/vdisk and io/File.c
# this Makefile will create virtual disk and modify LLFS

#APPS = .
#TARGETS = write	
#OBJS =  ./write.o 
#JUNKF = $(OBJS) *~
#JUNKD = *.dSYM
#CFLAGS  += -g -std=gnu11 -I.
#all: $(TARGETS)
#$(TARGETS): $(OBJS)
#tidy:
	#rm -f $(JUNKF); rm -rf $(JUNKD)
#clean:
	#rm -f $(JUNKF) $(TARGETS); rm -rf $(JUNKD)

all: vdisk write read delete
vdisk: 
	cd ../io && $(MAKE)
write: write.o
	gcc -o write write.o
write.o:
	gcc -c write.c -o write.o 

read: read.o
	gcc -o read read.o
read.o:
	gcc -c read.c -o read.o  
delete: delete.o
	gcc -o delete delete.o
delete.o:
	gcc -c delete.c -o delete.o

clean:
	-rm -f *.o
#rm -f $(JUNKF) $(TARGETS); rm -rf $(JUNKD)
	
