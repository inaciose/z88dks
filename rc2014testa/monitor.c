#include <stdio.h>

int fputc_cons_native(char c) __naked
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

int fgetc_cons() __naked
{
__asm
    push    bc
    push    af
    ld      c, 01h
    rst     30h
    ld      l,a     ;Return the result in hl
    ld      h,0
    pop     af
    pop     bc

__endasm;
}
