#CFLAGS = +rc2014 -c -o $@
#CC = zcc
#$(CC)

all:
	 
	zcc +rc2014 -clib=rc2014-8085 -o test.o -subtype=none --no-crt -Ca '-l' -Cz '--org 0x8500' test.c monitor.c -create-app

clean:
	rm -f test_DATA.bin test.map test.bin test.o test.hex

