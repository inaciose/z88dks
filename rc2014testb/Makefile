#CFLAGS = +rc2014 -c -o $@
#CC = zcc
#$(CC)

all:
	zcc +rc2014 -subtype=basic -clib=sdcc_iy -o test.o test.c -SO3 -v -m --list -pragma-define:CRT_ORG_CODE=0x8500 -create-app

clean:
	rm -f *.c.lis test_DATA.bin test_BSS.bin test_CODE.bin test.map test.bin test.o test.lis test.hex test.ihx

