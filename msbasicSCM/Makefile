all:
	zcc +z80 --no-crt -v -m --list -Ca-f0xFF scmbasic.asm -o basic
	z88dk-appmake +glue -b basic --ihex --pad --filler 0xFF --recsize 24 --clean

clean:
	rm -f basic.lis basic__.bin basic.map basic__.ihx
