all:
	zcc +rc2014 -subtype=basic -clib=sdcc_iy -o test.o test.c ztgsdcardapi.c -SO3 -v -m --list --max-allocs-per-node100000 -pragma-define:CRT_ORG_CODE=0x8500 -pragma-define:REGISTER_SP=0xFC00 -create-app

clean:
	rm -f *.c.lis test_DATA.bin test_BSS.bin test_CODE.bin test.map test.bin test.o test.lis test.hex test.ihx