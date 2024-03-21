docker run -v ${PWD}:/src/ -it z88dk/z88dk make

srec_cat test.bin -binary -offset 0x8500 -output test.hex -intel -address-length=2

