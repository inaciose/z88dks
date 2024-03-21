#CFLAGS = +rc2014 -c -o $@
#CC = zcc
#$(CC)

all:
	 
	zcc +z80 -clib=classic -o test.o test.c monitor.c -pragma-define:CRT_ORG_CODE=0x8500 -create-app -m

test.o: test.c

clean:
	rm -f test_DATA.bin test.map test.bin test.o test.hex

