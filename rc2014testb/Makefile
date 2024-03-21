all:
	zcc +rc2014 -subtype=basic -clib=sdcc_iy -o test.o test.c -SO3 -v -m -w --list --max-allocs-per-node100000 -pragma-define:CRT_ORG_CODE=0x8500 -pragma-define:REGISTER_SP=0xFC00 -create-app


debug:
	zcc +rc2014 -subtype=basic -clib=sdcc_iy -o test.o test.c -SO3 -v -m -w --list --max-allocs-per-node100000 -pragma-define:CRT_ORG_CODE=0x8500 -pragma-define:REGISTER_SP=0xFC00 -create-app  --c-code-in-asm --fverbose-asm


clean:
	rm -f *.c.lis test_DATA.bin test_BSS.bin test_CODE.bin test.map test.bin test.o test.lis test.hex test.ihx

