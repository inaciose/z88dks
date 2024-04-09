#include <stdio.h>

/*
/* Passing arguments btw C and asm
/* zcc +rc2014 -subtype=basic -clib=sdcc_iy
/* I notice that the ret instruction, is required
/* It seeams that we dont need to preserve hl (push/pop)
*/

/////////////////////////////////////////////////////
// API function $01, input character
//
// Parameters: none
// Returns: A = Character input from console
//
// args: no argument
// ret: l

char scm_getc(void) __naked
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

/*
/////////////////////////////////////////////////////
// API function $02, output character
//
// Parameters: A = Character to output to console
// Returns: A = Character output to console
//
// args: one char arg
// ret: none (l, hl, dehl)
// arg in the stack. 
// first 2 bytes allways hold the return address
// next byte is the argument 

void scm_putc(char c) __naked
{
    #asm

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

    #endasm
}
*/

/////////////////////////////////////////////////////
// API function $03, input status
//
// Parameters: none
// Returns: NZ flagged if an input character is available from the console
//
// args: no argument
// ret: l (0= not available / char code that is available)

char scm_agetc(void) __naked
{
    #asm

    push af
    push bc;
    push de

    ld      c, 0x03
    rst     0x30

    jr z, aget_noa
    ; is available
    ld      l,a
    jr aget_end

    aget_noa:
    ; not available
    ld      l,0 
   
    aget_end:
    ld      h,0     ; return the result in hl

    pop de
    pop bc
    pop af

    ret

    #endasm
}

/*
/////////////////////////////////////////////////////
// API function $06, output line
//
// Parameters: DE = Start of line in memory
// Returns: none
//
// args: one int arg
// ret: none (l, hl, dehl)
// arg in the stack. 
// first 2 bytes allways hold the return address
// next 2 byte are the argument (int = 16bit)
// LSB first

void scm_printline(char *s) __naked
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

    ld      c, 0x06
    rst     0x30

    pop de
    pop bc
    pop af

    ret

    #endasm
}
*/

/*
/////////////////////////////////////////////////////
// API function $0A, delay
//
// Parameters: DE = Number of milliseconds delay
// Returns: none
//
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
*/

/*
/////////////////////////////////////////////////////
// API function $28, get top of free memory
//
// Parameters: none
// Returns: DE = Highest location not in use by the Monitor
//
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
// API function $29, set top of free memory
//
// Parameters: DE = Highest location not in use by the Monitor
// Returns: none
//
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
*/