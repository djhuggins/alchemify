# 

all: source binary

binary: doublealchemify.c libdoublealchemify.c libdoublealchemify.h
	gcc -c -ansi doublealchemify.c libdoublealchemify.c
	gcc -o doublealchemify doublealchemify.o libdoublealchemify.o

clean:
	rm -f *.o doublealchemify


