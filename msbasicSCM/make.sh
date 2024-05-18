docker run -v ${PWD}:/src/ -it z88dk/z88dk make

srec_cat basic__.bin -binary -offset 0x8000 -output scmbasic.hex -intel -address-length=2
