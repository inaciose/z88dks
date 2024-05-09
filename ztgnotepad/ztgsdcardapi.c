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

    // store all the other
    // register in the stack
    push af
    push bc;
    push de

    // get input filename *str
    // load it to de register
    ; LSB first (16bit)
    ld e,(hl)
    inc hl
    ld d,(hl)

    // store hl (it have the next argumen address)
    push hl

    //
    // store filename string in 
    // required memory start address
    //

    // set destination address
    // for the file name string
    ld hl, ZTI_NAME
    
    // copy the sring from *de to *hl
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

    // advance to START address
    // point to the first LSB on stack
    pop hl
    inc hl

    // get input START start address
    // load it to de register
    ld e,(hl)
    inc hl
    ld d,(hl)
        
    // store hl (is required? no need to get any more arg from stack)
    push hl

    //
    // store start address START in
    // required memory start address
    //

    // set destination address
    // for the start address
    ld hl, ZTI_START
    ld (hl), d
    inc hl
    ld (hl), e

    // (is required if close above push)
    pop hl

    // store hl (is required?)
    push hl

    // call the load routine (ROM)
    call ZTC_FLOAD

    // (is required if close above push)
    pop hl

    //
    // set the return value in hl register to
    // the num bytes loaded from api call output
    // memory address
    //
    ld de, ZTO_NBYTES
    ld h, (de)
    inc de
    ld l, (de)

    // restore all the other
    // register in the stack
    pop de
    pop bc
    pop af

    // ready to return
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

    // store all the other
    // register in the stack
    push af
    push bc;
    push de

    // get input filename *str
    // load it to de register
    ; LSB first (16bit)
    ld e,(hl)
    inc hl
    ld d,(hl)

    // store hl (it have the next argumen address)
    push hl

    //
    // store filename string in 
    // required memory start address
    //

    // set destination address
    // for the file name string
    ld hl, ZTI_NAME
    
    // copy the sring from *de to *hl
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

    // get input START start address
    // load it to de register
    ld e,(hl)
    inc hl
    ld d,(hl)

    // store hl (it have the next argumen address)
    push hl

    //
    // store start address START in
    // required memory start address
    //

    // set destination address
    // for the start address
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

    // store hl (is required? no need to get any more arg from stack)
    push hl

    //
    // store lenght (nbytes) LEN in
    // required memory start address
    //

    // set destination address
    // for the len address
    ld hl, ZTI_LEN
    ld (hl), d
    inc hl
    ld (hl), e
   
    // (is required if close above push)
    pop hl

    // store hl (is required?)
    push hl

    // call the save routine (ROM)
    call ZTC_FSAVE

    // (is required if close above push)
    pop hl

    pop de
    pop bc
    pop af

    //
    // nothing to return in hl
    // the value it holds
    // is non sense
    //

    ret

    //
    // code not required
    // if not debuging
    //

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

/////////////////////////////////////////////////////
//
// debug snipets
/////////////////////////////////////////////////////
/*
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
*/
/////////////////////////////////////////////////////
/*
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
*/
/////////////////////////////////////////////////////

/////////////////////////////////////////////////////

/////////////////////////////////////////////////////
