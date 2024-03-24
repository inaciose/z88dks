#include <stdio.h>

// this one is not working
int fgetc_cons() __naked
{
__asm
    push af
    push bc;
    push de

    ld      c, 0x01
    rst     0x30
    ld      l,a     ; return the 
    ld      h,0     ; result in hl

    pop de
    pop bc
    pop af

    ret
__endasm;
}

// this one works
int fputc_cons_native(char c) __naked
{
__asm
    ld hl,2                 ; skip over return
    add hl,sp               ; address on stack

    push af
    push bc;
    push de

    ld a,(hl)
    ld c, 0x02
    rst 0x30
    
    pop de
    pop bc
    pop af

    ret
__endasm;
}
