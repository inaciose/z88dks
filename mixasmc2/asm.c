#include <stdio.h>

/*
/* Passing arguments btw C and asm
/* zcc +rc2014 -subtype=basic -clib=sdcc_iy
/* I notice that the ret instruction, is required
/* It seeams that we dont need to preserve hl (push/pop)
*/

/////////////////////////////////////////////////////
// args: one char arg
// ret: none (l, hl, dehl)
// arg in the stack. 
// first 2 bytes allways hold the return address
// next byte is the argument 

void mputc(char c) __naked
{
    #asm

    ld hl,2
    add hl,sp              ; skip over return address on stack

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

    #endasm
}

/////////////////////////////////////////////////////
// args: no argument
// ret: l

char mgetc(void) __naked
{
    #asm

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

    #endasm
}

/////////////////////////////////////////////////////
// args: two char args
// ret: none (l, hl, dehl)
// they are in consecutive bytes on the stack
// after 2 bytes with return address
// return stack as received 

void mput2c(char c, char d) __naked
{
    #asm

    ld hl,2                 ; skip over return 
    add hl,sp               ; address on stack

    push af
    push bc;
    push de

    ld a,(hl)
    
    ; hl must be preserved in rst 30, 2
    ; we could also load the next arg in b register
    ; inc hl
    ; ld b,(hl)
    ; and follow other path
    
    push hl
    ld c, 0x02
    rst 0x30
    pop hl

    inc hl
    ld a,(hl)
    ld c, 0x02
    rst 0x30

    pop de
    pop bc
    pop af

    ret

    #endasm
}

/////////////////////////////////////////////////////
// args: no argument
// ret: hl

int scm_freetop(void) __naked
{
    #asm

    push af
    push bc;
    push de


    ld      c, 0x28
    rst     0x30
    ld      l,e     ; return the
    ld      h,d     ; result in hl

    pop de
    pop bc
    pop af

    ret

    #endasm
}

/////////////////////////////////////////////////////
// args: one int arg
// ret: none (l, hl, dehl)
// arg in the stack. 
// first 2 bytes allways hold the return address
// next 2 byte are the argument (int = 16bit)
// LSB first

void scm_setfreetop(int top) __naked
{
    #asm

    ld hl,2                 ; skip over return 
    add hl,sp               ; address on stack

    push af
    push bc;
    push de

    ; LSB first (16bit)
    ld e,(hl)
    inc hl
    ld d,(hl)

    ld      c, 0x29
    rst     0x30

    pop de
    pop bc
    pop af

    ret

    #endasm
}

/////////////////////////////////////////////////////
// args: one int arg
// ret: none (l, hl, dehl)
// arg in the stack. 
// first 2 bytes allways hold the return address
// next 2 byte are the argument (int = 16bit)
// LSB first

void scm_delay(int ms) __naked
{
    #asm

    ld hl,2                 ; skip over return 
    add hl,sp               ; address on stack

    push af
    push bc;
    push de

    ; LSB first (16bit)
    ld e,(hl)
    inc hl
    ld d,(hl)

    ld      c, 0x0A
    rst     0x30

    pop de
    pop bc
    pop af

    ret

    #endasm
}




void mprintsrt(char *s) __naked
{
   #asm

    ld hl,2                 ; skip over return 
    add hl,sp               ; address on stack

    push af
    push bc;
    push de
    ;push hl

    ; LSB first (16bit)
    ld e,(hl)
    inc hl
    ld d,(hl)

    ld      c, 0x06
    rst     0x30

    ;pop hl
    pop de
    pop bc
    pop af

    ret

    #endasm
}
