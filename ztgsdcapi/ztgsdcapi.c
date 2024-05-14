#include <stdio.h>
/////////////////////////////////////////////////////
//
// ZTGSDC file system calls api
//
/////////////////////////////////////////////////////
//
// Define ztgsdc api calls addresses
//
#define ZTC_FSAVE       0x2002
#define ZTC_FLOAD       0x2005

#define ZTC_FDEL        0x2008
#define ZTC_SLIST       0x200b
#define ZTC_CLIST       0x200e
#define ZTC_FREN        0x2011
#define ZTC_FCOPY       0x2014
#define ZTC_CD          0x2017
#define ZTC_CWD         0x201a
#define ZTC_MKDIR       0x201d
#define ZTC_RMDIR       0x2020
#define ZTC_FEXIST      0x2023
#define ZTC_RESET       0x2026
#define ZTC_STATUS      0x2029
#define ZTC_FOPEN       0x202c
#define ZTC_FCLOSE      0x202f
#define ZTC_FWRITE      0x2032
#define ZTC_FREAD       0x2035
#define ZTC_FTELL       0x2038
#define ZTC_FSEEKSET    0x203b
#define ZTC_FSEEKCUR    0x203e
#define ZTC_FSEEKEND    0x2041

#define ZTC_FREWIND     0x2044
#define ZTC_FPEEK       0x2047

/////////////////////////////////////////////////////
//
// Define ztgsdc api input args addresses
//
#define ZTI_START   0xfa00
#define ZTI_LEN     0xfa02

#define ZTI_NAME    0xfa04
#define ZTI_NAME1   0xfa45

//#define ZTI_MODE    0xfa86
#define ZTI_MODE    ZTI_START
#define ZTI_HDL     0xfa88

/////////////////////////////////////////////////////
//
// Define ztgsdc api output results addresses
//
#define ZTO_ERROR   0xfa99
#define ZTO_BYTE    0xfa9a
#define ZTO_BYTE1   0xfa9b
#define ZTO_LONG    0xfa9c

#define ZTO_NBYTES  0xfaa0
#define ZTO_BUFFER  0xfaa2

/////////////////////////////////////////////////////
// fopen, open file on specific mode
//
// Parameters: passed on stack
// Returns: bytes read on hl
//
// arg in the stack.
// LSB first
// first 2 bytes allways hold the return address
// next 2 byte are the filename pointer (int = 16bit)
// next 2 byte are the mode address (int = 16bit)

int ztgsdc_fopen(char *s, int mode) __naked
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
    
    // copy the string from *de to *hl
    call ZSTRCPY2HL

    // advance to open MODE address
    // point to the first LSB on stack
    pop hl
    inc hl

    // get open MODE address
    // load it to de register
    ld e,(hl)
    inc hl
    ld d,(hl)

    // store hl (is required? no need to get any more arg from stack)
    //push hl

    //
    // store open mode MODE in
    // required memory start address
    //

    // set destination address
    // for the MODE address
    ld hl, ZTI_MODE
    ld (hl), d
    inc hl
    ld (hl), e

    // (is required if close above push)
    //pop hl

    // store hl (is required?)
    //push hl

    // call the load routine (ROM)
    call ZTC_FOPEN

    // (is required if close above push)
    //pop hl

    // set the return value in hl register to
    // handle id or error id
    // check error
    ld de, ZTO_ERROR
    ld a, (de)
    or 0
    jr z, ZFOPENOK
        ld h, 0xf
        ld l, a
        jr ZFOPENEND
    ZFOPENOK:
        ld h, 0x0
        ld de, ZTO_BYTE
        ld l, (de)

    ZFOPENEND:

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
// fclose - close opened file by handle id
//
// Parameters: passed on stack
// Returns: bytes read on hl
//
// arg in the stack.
// LSB first
// first 2 bytes allways hold the return address
// next 2 byte are the mode (byte) pointer (int = 16bit)
// returns in hl: 0 = ok / else = error

int ztgsdc_fclose(int handle) __naked
{

   #asm

    ld hl,2                 ; skip over return 
    add hl,sp               ; address on stack

    // store all the other
    // register in the stack
    push af
    push bc;
    push de

    // get input handle id
    // load it to de register
    ; LSB first (16bit)
    ld e,(hl)
    inc hl
    ld d,(hl)

    // store hl (it have the next argumen address)
    //push hl

    // store value in file HDL address
    // invert byte order LSB first
    // because we only use a byte
    ld hl, ZTI_HDL
    ld (hl), e
    inc hl
    ld (hl), d

    // no more arguments, no need to push it
    //pop hl

    // call api function
    call ZTC_FCLOSE

    // set result on hl (low)
    // by check error address
    ld h, 0x0
    ld de, ZTO_ERROR
    ld l, (de)

    // restore all the
    // other registers
    pop de
    pop bc
    pop af

    ret

    #endasm
}


/////////////////////////////////////////////////////
// fwrite byte 
//
// Parameters: passed on stack
// Returns: bytes read on hl
//
// arg in the stack.
// LSB first
// first 2 bytes allways hold the return address
// next 2 byte are the mode (byte) pointer (int = 16bit)
// returns in hl: 0 = ok / else = error

int ztgsdc_fwrite(int handle, int b) __naked
{

   #asm

    ld hl,2                 ; skip over return 
    add hl,sp               ; address on stack

    // store all the other
    // register in the stack
    push af
    push bc;
    push de

    // get input handle id
    // load it to de register
    ; LSB first (16bit)
    ld e,(hl)
    inc hl
    ld d,(hl)

    // store hl (it have the next argumen address)
    push hl

    // store value in file HDL address
    // invert byte order LSB first
    // because we only use a byte
    ld hl, ZTI_HDL
    ld (hl), e
    inc hl
    ld (hl), d

    // restore hl
    pop hl

    // advance to START address
    // point to the first LSB on stack
    inc hl

    // get input START start address
    // load it to de register
    ld e,(hl)
    inc hl
    ld d,(hl)
        
    //
    // store start address START in
    // required memory start address
    //

    // set destination address
    // for the start address
    // invert byte order LSB first
    // because we only use a byte
    ld hl, ZTI_START
    ld (hl), e
    inc hl
    ld (hl), d

    // call api function
    call ZTC_FWRITE

    // set the return value in hl register to
    // handle id or error id
    // check error
    ld de, ZTO_ERROR
    ld a, (de)
    or 0
    jr z, ZFWRITEOK
        ld h, 0xf
        ld l, a
        jr ZFWRITEEND
    ZFWRITEOK:
        ld h, 0x0
        ld de, ZTO_BYTE1
        ld l, (de)

    ZFWRITEEND:

    // restore all the
    // other registers
    pop de
    pop bc
    pop af

    ret

    #endasm
}


/////////////////////////////////////////////////////
// fread byte 
//
// Parameters: passed on stack
// Returns: bytes read on hl
//
// arg in the stack.
// LSB first
// first 2 bytes allways hold the return address
// next 2 byte are the handle (LSB byte int = 16bit)
// next 2 byte are the result address pointer (int = 16bit)
// returns in hl: byte read LSB / or error if res != 1

int ztgsdc_fread(int handle, int *res) __naked
{

   #asm

    ld hl,2                 ; skip over return 
    add hl,sp               ; address on stack

    // store all the other
    // register in the stack
    push af
    push bc;
    push de

    // get input handle id
    // load it to de register
    ; LSB first (16bit)
    ld e,(hl)
    inc hl
    ld d,(hl)

    // store hl (it have the next argumen address)
    push hl

    // store value in file HDL address
    // invert byte order LSB first
    // because we only use a byte
    ld hl, ZTI_HDL
    ld (hl), e
    inc hl
    ld (hl), d


    // call api function
    call ZTC_FREAD
    
    // restore hl
    pop hl

    // advance to result byte destination address
    // point to the first LSB on stack
    inc hl

    // get destination address
    // load it to de register
    ld e,(hl)
    inc hl
    ld d,(hl)

    // we have the destination address

    // set the source address
    ld hl, ZTO_BYTE1
    // copy byte from src to dest address
    ld a, (hl)
    ld (de), a

    // set the return value in hl register to
    // handle id or error id
    // check error
    ld de, ZTO_ERROR
    ld a, (de)
    or 0
    jr z, ZFREADOK
        ld h, 0xf
        ld l, a
        jr ZFREADEND
    ZFREADOK:
        ld h, 0x0
        ld de, ZTO_BYTE
        ld l, (de)

    ZFREADEND:

    // restore all the
    // other registers
    pop de
    pop bc
    pop af

    ret

    #endasm
}

/////////////////////////////////////////////////////
// fpeek byte 
//
// Parameters: passed on stack
// Returns: bytes read on hl
//
// arg in the stack.
// LSB first
// first 2 bytes allways hold the return address
// next 2 byte are the handle (LSB byte int = 16bit)
// returns in hl: byte read LSB / FF maybe end of file

int ztgsdc_fpeek(int handle) __naked
{

   #asm

    ld hl,2                 ; skip over return 
    add hl,sp               ; address on stack

    // store all the other
    // register in the stack
    push af
    push bc;
    push de

    // get input handle id
    // load it to de register
    ; LSB first (16bit)
    ld e,(hl)
    inc hl
    ld d,(hl)

    // store hl (it have the next argumen address)
    //push hl

    // store value in file HDL address
    // invert byte order LSB first
    // because we only use a byte
    ld hl, ZTI_HDL
    ld (hl), e
    inc hl
    ld (hl), d

    // call api function
    call ZTC_FPEEK
    
    // restore hl
    //pop hl

    // set the return value in hl register to
    // handle id or error id
    // check error
    ld de, ZTO_ERROR
    ld a, (de)
    or 0
    jr z, ZFPEEKOK
        ld h, a
        ld de, ZTO_BYTE
        ld l, (de)
        jr ZFPEEKEND
    ZFPEEKOK:
        ld h, 0x0
        ld de, ZTO_BYTE
        ld l, (de)
    ZFPEEKEND:

    // restore all the
    // other registers
    pop de
    pop bc
    pop af

    ret

    #endasm
}


/////////////////////////////////////////////////////
// frewind - set position at begin of file
//
// Parameters: passed on stack
// Returns: bytes read on hl
//
// arg in the stack.
// LSB first
// first 2 bytes allways hold the return address
// next 2 byte are the hdl (only LSB byte of int = 16bit)
// returns in hl: 0 = ok / else = error

int ztgsdc_frewind(int handle) __naked
{

   #asm

    ld hl,2                 ; skip over return 
    add hl,sp               ; address on stack

    // store all the other
    // register in the stack
    push af
    push bc;
    push de

    // get input handle id
    // load it to de register
    ; LSB first (16bit)
    ld e,(hl)
    inc hl
    ld d,(hl)

    // store hl (it have the next argumen address)
    //push hl

    // store value in file HDL address
    // invert byte order LSB first
    // because we only use a byte
    ld hl, ZTI_HDL
    ld (hl), e
    inc hl
    ld (hl), d

    // no more arguments, no need to push it
    //pop hl

    // call api function
    call ZTC_FREWIND

    // set result on hl (low)
    // by check error address
    ld h, 0x0
    ld de, ZTO_ERROR
    ld l, (de)

    // restore all the
    // other registers
    pop de
    pop bc
    pop af

    ret

    #endasm
}


/////////////////////////////////////////////////////
// ftell, get position on file 
//
// Parameters: passed on stack
// Returns: bytes read on hl
//
// arg in the stack.
// LSB first
// first 2 bytes allways hold the return address
// next 2 byte are the handle (LSB byte int = 16bit)
// returns in hl: byte read LSB / FF maybe end of file

unsigned long int ztgsdc_ftell(int handle) __naked
{

   #asm

    ld hl,2                 ; skip over return 
    add hl,sp               ; address on stack

    // store all the other
    // register in the stack
    push af
    push bc;
    push de

    // get input handle id
    // load it to de register
    ; LSB first (16bit)
    ld e,(hl)
    inc hl
    ld d,(hl)

    // store hl (it have the next argumen address)
    //push hl

    // store value in file HDL address
    // invert byte order LSB first
    // because we only use a byte
    ld hl, ZTI_HDL
    ld (hl), e
    inc hl
    ld (hl), d

    // call api function
    call ZTC_FTELL
    
    // restore hl
    //pop hl
    pop de

    ld hl, ZTO_LONG
    ld d, (hl)
    inc hl
    ld e, (hl)   

    push de

    inc hl
    ld d, h
    ld e, l

    ld h, (de)
    inc de
    ld l, (de)

    pop de

    // set the return value in hl register to
    // handle id or error id
    // check error
    // ld de, ZTO_ERROR

    // restore all the
    // other registers
    //pop de
    pop bc
    pop af

    ret

    #endasm
}


/////////////////////////////////////////////////////
// fseekset, set position from beguin of file 
//
// Parameters: passed on stack
// Returns: bytes read on hl
//
// arg in the stack.
// LSB first
// first 2 bytes allways hold the return address
// next 2 byte are the handle (LSB byte int = 16bit)
// next 2 byte are the pointer (address) of an long (long = 32bit)
// returns in hl: byte read LSB / or error if res != 1

int ztgsdc_fseekset(int handle, unsigned long int *pos) __naked
{

   #asm

    ld hl,2                 ; skip over return 
    add hl,sp               ; address on stack

    // store all the other
    // register in the stack
    push af
    push bc;
    push de

    // get input handle id
    // load it to de register
    ; LSB first (16bit)
    ld e,(hl)
    inc hl
    ld d,(hl)

    // store hl (it have the next argumen address)
    push hl

    // store value in file HDL address
    // invert byte order LSB first
    // because we only use a byte
    ld hl, ZTI_HDL
    ld (hl), e
    inc hl
    ld (hl), d

    // restore hl
    pop hl

    // advance to LSW
    // point to the first LSB on stack
    inc hl

    // get position address
    // load it to de register
    ld e,(hl)
    inc hl
    ld d,(hl)

    // we get the LS bytes and words first
    // store value in file ZTI_LEN address
    ld hl, ZTI_LEN
    // invert byte order
    inc de
    ld a, (de)
    ld (hl), a
    // 
    inc hl
    dec de
    ld a, (de)
    ld (hl), a
    inc de


    // debug
    push hl
    push de
    push bc
    push af

    ld hl, ZTI_LEN
    ld d,(hl)
    inc hl
    ld e,(hl)

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
    // end debug

    // advance byte index
    inc de
 
    // store MSW in file START address
    ld hl, ZTI_START
    inc de
    ld a, (de)
    ld (hl), a
    inc hl
    dec de
    ld a, (de)
    ld (hl), a

    // debug
    push hl
    push de
    push bc
    push af

    ld hl, ZTI_START
    ld d,(hl)
    inc hl
    ld e,(hl)

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
    // end debug

    // call api function
    call ZTC_FSEEKSET
    
    // set the return value in hl register to
    // handle id or error id
    // check error
    ld de, ZTO_ERROR
    ld a, (de)
    or 0
    //jr z, ZFSEEKSETOK
        ld h, 0x0
        ld l, a
        jr ZFSEEKSETEND
    ZFSEEKSETOK:
        ld h, 0x0
        ld de, ZTO_BYTE1
        ld l, (de)

    ZFSEEKSETEND:

    // restore all the
    // other registers
    pop de
    pop bc
    pop af

    ret

    #endasm
}

/////////////////////////////////////////////////////
// fseekcur, set position from current position in file 
//
// Parameters: passed on stack
// Returns: bytes read on hl
//
// arg in the stack.
// LSB first
// first 2 bytes allways hold the return address
// next 2 byte are the handle (LSB byte int = 16bit)
// next 2 byte are the position, pointer (address) to an long (long = 32bit)
// returns in hl: byte read LSB / or error if res != 1

int ztgsdc_fseekcur(int handle, long int *pos) __naked
{

   #asm

    ld hl,2                 ; skip over return 
    add hl,sp               ; address on stack

    // store all the other
    // register in the stack
    push af
    push bc;
    push de

    // get input handle id
    // load it to de register
    ; LSB first (16bit)
    ld e,(hl)
    inc hl
    ld d,(hl)

    // store hl (it have the next argumen address)
    push hl

    // store value in file HDL address
    // invert byte order LSB first
    // because we only use a byte
    ld hl, ZTI_HDL
    ld (hl), e
    inc hl
    ld (hl), d

    // restore hl
    pop hl

    // advance to LSW
    // point to the first LSB on stack
    inc hl

    // get position address
    // load it to de register
    ld e,(hl)
    inc hl
    ld d,(hl)

    // we get the LS bytes and words first
    // store value in file ZTI_LEN address
    ld hl, ZTI_LEN
    // invert byte order
    inc de
    ld a, (de)
    ld (hl), a
    // 
    inc hl
    dec de
    ld a, (de)
    ld (hl), a
    inc de


    // debug
    push hl
    push de
    push bc
    push af

    ld hl, ZTI_LEN
    ld d,(hl)
    inc hl
    ld e,(hl)

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
    // end debug

    // advance byte index
    inc de
 
    // store MSW in file START address
    ld hl, ZTI_START
    inc de
    ld a, (de)
    ld (hl), a
    inc hl
    dec de
    ld a, (de)
    ld (hl), a

    // debug
    push hl
    push de
    push bc
    push af

    ld hl, ZTI_START
    ld d,(hl)
    inc hl
    ld e,(hl)

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
    // end debug

    // call api function
    call ZTC_FSEEKCUR
    
    // set the return value in hl register to
    // handle id or error id
    // check error
    ld de, ZTO_ERROR
    ld a, (de)
    or 0
    //jr z, ZFSEEKCUROK
        ld h, 0x0
        ld l, a
        jr ZFSEEKCUREND
    ZFSEEKCUROK:
        ld h, 0x0
        ld de, ZTO_BYTE1
        ld l, (de)

    ZFSEEKCUREND:

    // restore all the
    // other registers
    pop de
    pop bc
    pop af

    ret

    #endasm
}

/////////////////////////////////////////////////////
// fseekend, set position from the end of the file 
//
// Parameters: passed on stack
// Returns: bytes read on hl
//
// arg in the stack.
// LSB first
// first 2 bytes allways hold the return address
// next 2 byte are the handle (LSB byte int = 16bit)
// next 2 byte are the position, pointer (address) to an long (long = 32bit)
// returns in hl: byte read LSB / or error if res != 1

int ztgsdc_fseekend(int handle, long int *pos) __naked
{

   #asm

    ld hl,2                 ; skip over return 
    add hl,sp               ; address on stack

    // store all the other
    // register in the stack
    push af
    push bc;
    push de

    // get input handle id
    // load it to de register
    ; LSB first (16bit)
    ld e,(hl)
    inc hl
    ld d,(hl)

    // store hl (it have the next argumen address)
    push hl

    // store value in file HDL address
    // invert byte order LSB first
    // because we only use a byte
    ld hl, ZTI_HDL
    ld (hl), e
    inc hl
    ld (hl), d

    // restore hl
    pop hl

    // advance to LSW
    // point to the first LSB on stack
    inc hl

    // get position address
    // load it to de register
    ld e,(hl)
    inc hl
    ld d,(hl)

    // we get the LS bytes and words first
    // store value in file ZTI_LEN address
    ld hl, ZTI_LEN
    // invert byte order
    inc de
    ld a, (de)
    ld (hl), a
    // 
    inc hl
    dec de
    ld a, (de)
    ld (hl), a
    inc de


    // debug
    push hl
    push de
    push bc
    push af

    ld hl, ZTI_LEN
    ld d,(hl)
    inc hl
    ld e,(hl)

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
    // end debug

    // advance byte index
    inc de
 
    // store MSW in file START address
    ld hl, ZTI_START
    inc de
    ld a, (de)
    ld (hl), a
    inc hl
    dec de
    ld a, (de)
    ld (hl), a

    // debug
    push hl
    push de
    push bc
    push af

    ld hl, ZTI_START
    ld d,(hl)
    inc hl
    ld e,(hl)

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
    // end debug

    // call api function
    call ZTC_FSEEKEND
    
    // set the return value in hl register to
    // handle id or error id
    // check error
    ld de, ZTO_ERROR
    ld a, (de)
    or 0
    //jr z, ZFSEEKENDOK
        ld h, 0x0
        ld l, a
        jr ZFSEEKENDEND
    ZFSEEKENDOK:
        ld h, 0x0
        ld de, ZTO_BYTE1
        ld l, (de)

    ZFSEEKENDEND:

    // restore all the
    // other registers
    pop de
    pop bc
    pop af

    ret

    #endasm
}



/////////////////////////////////////////////////////
// mkdir - make directory
//
// Parameters: passed on stack
// Returns: bytes read on hl
//
// arg in the stack.
// LSB first
// first 2 bytes allways hold the return address
// next 2 byte are the filename pointer (int = 16bit)
// returns in hl: 0 = ok / else = error

int ztgsdc_mkdir(char *s) __naked
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
    
    // copy the string from *de to *hl
    call ZSTRCPY2HL

    // no more arguments, no need to push it
    pop hl

    // call api function
    call ZTC_MKDIR

    // set result on hl (low)
    // by check error address
    ld h, 0x0
    ld de, ZTO_ERROR
    ld l, (de)

    // restore all the
    // other registers
    pop de
    pop bc
    pop af

    ret

    #endasm
}


/////////////////////////////////////////////////////
// rmdir - remove directory
//
// Parameters: passed on stack
// Returns: bytes read on hl
//
// arg in the stack.
// LSB first
// first 2 bytes allways hold the return address
// next 2 byte are the filename pointer (int = 16bit)
// returns in hl: 0 = ok / else = error

int ztgsdc_rmdir(char *s) __naked
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
    
    // copy the string from *de to *hl
    call ZSTRCPY2HL

    // no more arguments, no need to push it
    pop hl

    // call api function
    call ZTC_RMDIR

    // set result on hl (low)
    // by check error address
    ld h, 0x0
    ld de, ZTO_ERROR
    ld l, (de)

    // restore all the
    // other registers
    pop de
    pop bc
    pop af

    ret

    #endasm
}


/////////////////////////////////////////////////////
// rmdir - remove directory
//
// Parameters: passed on stack
// Returns: bytes read on hl
//
// arg in the stack.
// LSB first
// first 2 bytes allways hold the return address
// next 2 byte are the filename pointer (int = 16bit)
// returns in hl: 0 = ok / else = error

int ztgsdc_cd(char *s) __naked
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
    
    // copy the string from *de to *hl
    call ZSTRCPY2HL

    // no more arguments, no need to push it
    pop hl

    // call api function
    call ZTC_CD

    // set result on hl (low)
    // by check error address
    ld h, 0x0
    ld de, ZTO_ERROR
    ld l, (de)

    // restore all the
    // other registers
    pop de
    pop bc
    pop af

    ret

    #endasm
}


/////////////////////////////////////////////////////
// cwd - get current work directory (supply a string pointer)
//
// Parameters: passed on stack
// Returns: bytes read on hl
//
// arg in the stack.
// LSB first
// first 2 bytes allways hold the return address
// next 2 byte are the string pointer (address = 16bit)
// returns in hl: 0 = ok / else = error

int ztgsdc_cwd(char *s) __naked
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

    // we need the destination
    // address later
    push de

    // store hl (it have the next argumen address)
    push hl

    // call api function
    call ZTC_CWD

    // no more arguments, no need to push it
    pop hl

    // get the destination address
    pop de

    // set destination address for
    // current directory name string
    ld hl, ZTO_BUFFER
    
    // copy the string from *hl to *de
    call ZSTRCPY

    // set result on hl (low)
    // by check error address
    ld h, 0x0
    ld de, ZTO_ERROR
    ld l, (de)

    // restore all the
    // other registers
    pop de
    pop bc
    pop af

    ret

    #endasm
}


/////////////////////////////////////////////////////
// check if file, or directory, name exist
//
// Parameters: passed on stack
// Returns: bytes read on hl
//
// arg in the stack.
// LSB first
// first 2 bytes allways hold the return address
// next 2 byte are the filename pointer (int = 16bit)
// returns in hl: 0 = not found / 1 = file / 2 = directory / 255 = error

int ztgsdc_fexist(char *s) __naked
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
    
    // copy the string from *de to *hl
    call ZSTRCPY2HL

    // no more arguments, no need to push it
    pop hl

    // call api function
    call ZTC_FEXIST

    // check error
    ld de, ZTO_ERROR
    ld a, (de)
    or 0
    jr z, ZFEXISTOK
        ld h, 0xf
        ld l, 0xf
        jr ZFEXISTEND
    ZFEXISTOK:
        ld h, 0x0
        ld de, ZTO_BYTE
        ld l, (de)

    ZFEXISTEND:
    // restore all the
    // other registers
    pop de
    pop bc
    pop af

    ret

    #endasm
}


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

int ztgsdc_fload(char *s, int start) __naked
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
    
    // copy the string from *de to *hl
    call ZSTRCPY2HL

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

void ztgsdc_fsave(char *s, int start, int len) __naked
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
    
    // copy the string from *de to *hl
    call ZSTRCPY2HL

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


    #endasm
}


/////////////////////////////////////////////////////
// dummy function for shared routines
/////////////////////////////////////////////////////
void ztgsdc_dummy(void) __naked
{

   #asm

    ld hl,2                 ; skip over return 
    add hl,sp               ; address on stack

    // store all the other
    // register in the stack
    push af
    push bc;
    push de

    pop de
    pop bc
    pop af

    ret
    

    //
    // required functions
    // shared bw some of them
    //

    // copy the string from *de to *hl
    ZSTRCPY2HL:
                ld a, (de)
                or 0
                jr z, ZSTRCPY2HL1
                ld (hl), a
                inc hl
                inc de
                jr ZSTRCPY2HL

    ZSTRCPY2HL1:
                // filename stored 
                // add string terminator
                ld (hl), 0
                ret

    // copy the string from *hl to *de
    ZSTRCPY:
                ld a, (hl)
                or 0
                jr z, ZSTRCPY1
                ld (de), a
                inc hl
                inc de
                jr ZSTRCPY

    ZSTRCPY1:
                // filename stored 
                // add string terminator
                ld (de), 0
                ret


    //
    // code not required
    // only debug code
    //

    // debug code
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

    // debug code
    OUTC:
    ; char input on a
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
