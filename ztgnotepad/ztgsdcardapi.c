#include <stdio.h>
/////////////////////////////////////////////////////
//
// ZTdos system calls api
//
/////////////////////////////////////////////////////
//
// Define ztdos api calls addresses
//
#define ZTC_FSAVE 0x2002
#define ZTC_FLOAD 0x2005

#define ZTC_FDEL    0x2008
#define ZTC_SLIST   0x200b
#define ZTC_CLIST   0x200e
#define ZTC_FREN    0x2011
#define ZTC_FCOPY   0x2014


/////////////////////////////////////////////////////
//
// Define ztdos api input args addresses
//
#define ZTI_START   0xfa00
#define ZTI_LEN     0xfa02

#define ZTI_NAME    0xfa04
#define ZTI_NAME1   0xfa45

#define ZTI_MODE    0xfa86
#define ZTI_HDL     0xfa88

/////////////////////////////////////////////////////
//
// Define ztdos api output results addresses
//
#define ZTO_ERROR   0xfa99
#define ZTO_BYTE    0xfa9a
#define ZTO_BYTE1   0xfa9b
#define ZTO_LONG    0xfa9c

#define ZTO_NBYTES  0xfaa0
#define ZTO_BUFFER  0xfaa2

/////////////////////////////////////////////////////
// load file to sd card
//
// Parameters: passed on stack
// Returns: bytes read on hl
//
// arg in the stack.
// LSB first
// first 2 bytes allways hold the return address
// next 2 byte are the filename pointer (int = 16bit)
// next 2 byte are the start address (int = 16bit)

int ztgsdcard_load(char *s, int start) __naked
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


    // debug
    push hl
    push de
    push bc
    push af
    // debug
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
    
    // debug
    pop af
    pop bc
    pop de
    pop hl


    push hl

    // store filename in memory exchange position
    // TODO: HARDCODED FNAME dest start address
    //ld hl, 0xfaf4
    //ld hl, 0xfaf6
    //ld hl, 0xfa04
    ld hl, ZTI_NAME
    
    LFNL:
    ld a, (de)
    or 0
    jr z, LFS
    ld (hl), a
    inc hl
    inc de
    jr LFNL

    LFS:
    // filename stored 
    // add string terminator
    ld (hl), 0

    // debug
    push hl
    push de
    push bc
    push af
    ld   de,ZTI_NAME
    ld   C,0x06
    rst  0x30
    ld a, '\n'
    call OUTC
    ld a, '\r'
    call OUTC
    pop af
    pop bc
    pop de
    pop hl

    // advance to start address
    // point to the first LSB on stack
    pop hl
    inc hl

    // get start var
    ld e,(hl)
    inc hl
    ld d,(hl)

    
    // debug
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
    // TODO: HARDCODED FSTART dest start address
    //ld hl, 0xfae0
    //ld hl, 0xfae2
    ld hl, ZTI_START
    ld (hl), d
    inc hl
    ld (hl), e

    pop hl

    // call the load rom routine
    push hl
    // TODO hardcoded address
    call ZTC_FLOAD
    //call 0x2005
    //call 0x2225
    //call 0x8225 
    pop hl


    // debug
    ld hl, ZTO_NBYTES
    ld d, (hl)
    inc hl
    ld e, (hl)

    // debug
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


    // get bytes loaded
    //ld de, 0xfae0
    ld de, ZTO_NBYTES
    ld h, (de)
    inc de
    ld l, (de)

    pop de
    pop bc
    pop af

    ret
   
    #endasm
}

/////////////////////////////////////////////////////
// save file to sd card
//
// Parameters: passed on stack
// Returns: none
//
// arg in the stack.
// LSB first
// first 2 bytes allways hold the return address
// next 2 byte are the filename pointer (int = 16bit)
// next 2 byte are the start address (int = 16bit)
// next 2 byte are the len (int = 16bit)

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
    // TODO: HARDCODED FNAME dest start address
    //ld hl, 0xfaf4
    //ld hl, 0xfaf6
    //ld hl, 0xfa04
    ld hl, ZTI_NAME
    
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

    /*
    // debug
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
    */

    push hl

    // store it
    // TODO: HARDCODED FSTART dest start address
    //ld hl, 0xfae0 
    //ld hl, 0xfae2
    ld hl, ZTI_START
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

    /*
    // debug
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
    */

    push hl

    // store it
    // TODO: HARDCODED FLEN dest start address
    //ld hl, 0xfae2
    //ld hl, 0xfae4
    ld hl, ZTI_LEN
    ld (hl), d
    inc hl
    ld (hl), e
   
    pop hl

    // call the save rom routine
    push hl
    // TODO hardcoded address
    call ZTC_FSAVE
    //call 0x2002
    //call 0x2182
    //call 0x8182
    pop hl

    pop de
    pop bc
    pop af

    ret


    //
    // debug code
    //

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

    //
    // debug code
    //

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