# Z80 RC2014 Z88dk, passing arguments btw C and asm

Some code to passing arguments btw C and asm in Z88dk. The code is calling SCM api.

Local variables are passed using the stack
Sharing global Names (variables and functions), is not cover here

- https://github.com/z88dk/z88dk
- https://smallcomputercentral.com/

zcc +rc2014 -subtype=basic -clib=sdcc_iy

Some remarks:
- Noticed that the ret instruction, is required
- seeams that we dont need to preserve hl (push/pop)


Some links:
- https://github.com/z88dk/z88dk/wiki/CallingConventions
- https://github.com/z88dk/z88dk/wiki/The-Stack-Frame
- https://www.z88dk.org/wiki/doku.php?id=temp%3Afront#mixing_c_and_assembly_language
