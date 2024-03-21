CFLAGS = +zx -c -o $@
CC = zcc

all: test.o 
	$(CC) +zx -lndos -o$@ -create-app test.o 

test.o: test.c

clean:
	rm -f all all.tap test.bin test.o
