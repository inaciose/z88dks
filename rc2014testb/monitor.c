#include <stdio.h>

int fputc_cons(char c) __naked
{
__asm
    pop     bc  ;return address
    pop     hl  ;character to print in l
    push    hl
    push    bc
    ld      a,l
    push    hl
    push    bc
    ld      c, 02h
    rst     30h
    pop     bc
    pop     hl
__endasm;
} 
