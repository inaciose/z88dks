#CFLAGS = +rc2014 -c -o $@
#CC = zcc
#$(CC)

all:
	zcc +z80 -clib=classic -o test.o test.c monitor.c -pragma-define:CRT_ORG_CODE=0x8500 -pragma-define:REGISTER_SP=0xFC00 -create-app -m --list

clean:
	rm -f *.c.lis test_DATA.bin test.map test.bin test.o test.lis test.hex

