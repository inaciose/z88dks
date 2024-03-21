#include <stdio.h>

// this one is not working
int fgetc_cons() __naked
{
__asm
    push    bc
    ld      c, 0x01
    rst     0x30
    ld      l,a     ;Return the result in hl
    ld      h,0
    pop     bc

__endasm;
}

// this one works
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
    ld      c, 0x02
    rst     0x30
    pop     bc
    pop     hl
__endasm;

}

