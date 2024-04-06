#include <stdio.h>

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

void ztgsdcard_save(char *s, int start, int len) __naked
{

   #asm

    ld hl,2                 ; skip over return 
    add hl,sp               ; address on stack

    push af
    push bc;
    push de

    // get filename s*
    ; LSB first (16bit)
    ld e,(hl)
    inc hl
    ld d,(hl)

    push hl

    // store filename in memory exchange position
    ld hl, 0xfaf4 ; FNAME dest start address
    
    FNL:
    ld a, (de)
    or 0
    jr z, SFS
    ld (hl), a
    inc hl
    inc de
    jr FNL

    SFS:
    // filename stored 
    // add string terminator
    ld (hl), 0

    // advance to start address
    // point to the first LSB on stack
    pop hl
    inc hl

    // get start var
    ld e,(hl)
    inc hl
    ld d,(hl)

    // display start 2 bytes
    push de
    ld a, d
    call NUM2HEX
    ld a, d
    call OUTC
    ld a, e
    call OUTC
    pop de

    push de
    ld a, e
    call NUM2HEX
    ld a, d
    call OUTC
    ld a, e
    call OUTC
    pop de

    ld a, '\n'
    call OUTC

    ld a, '\r'
    call OUTC
    // end display


    push hl

    // store it
    ld hl, 0xfae0 ; FSTART dest start address
    ld (hl), d
    inc hl
    ld (hl), e

    // start stored, advance to file len
    SFL:
    // point to the first LSB on stack
    pop hl
    inc hl

    // get len var
    ld e,(hl)
    inc hl
    ld d,(hl)    

    // display len 2 bytes
    push de
    ld a, d
    call NUM2HEX
    ld a, d
    call OUTC
    ld a, e
    call OUTC
    pop de

    push de
    ld a, e
    call NUM2HEX
    ld a, d
    call OUTC
    ld a, e
    call OUTC
    pop de

    ld a, '\n'
    call OUTC

    ld a, '\r'
    call OUTC
    // end display

    push hl

    // store it
    ld hl, 0xfae2 ; FLEN  dest start address
    ld (hl), d
    inc hl
    ld (hl), e
   
    pop hl

    push hl
    call 0x2182
    pop hl

    pop de
    pop bc
    pop af

    ret

    ;

    NUM2HEX:
    ; input on a
    ; result on de
    push bc
    ld c, a   ; a = number to convert
    call NUM2HEX1
    ld d, a
    ld a, c
    call NUM2HEX2
    ld e, a
    pop bc
    ret  ; return with hex number in de

    NUM2HEX1:
    rra
    rra
    rra
    rra
    NUM2HEX2:        
    or 0xF0
    daa
    add a, 0xA0
    adc a, 0x40 ; Ascii hex at this point (0 to F)   
    ret     

    ;
    OUTC:
    push hl
    push af
    push bc;
    push de

    ld c, 0x02
    rst 0x30
    
    pop de
    pop bc
    pop af
    pop hl

    ret


    #endasm
}