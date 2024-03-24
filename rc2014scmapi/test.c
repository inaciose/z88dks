#include <stdio.h>
#include "scmonitor.h"

/*
extern char scm_getc(void);
extern void scm_putc(char c);
extern char scm_aget(void);
extern void scm_printline(char *s);
extern void scm_delay(int ms);
extern int scm_freetop(void);
extern void scm_setfreetop(int top);
*/

char msg_freetop[] = "Memory top\n\r\0";

int main(void)
{
    int f = 0;

    printf("Testing...\n\r");

    scm_putc('S');
    scm_putc('\n');
    scm_putc('\r');

    // free top
    scm_printline(msg_freetop);

    // get & print
    int ft = scm_freetop();
    printf("%x\n\r", ft);

    // set
    scm_setfreetop(0xFBAB);

    // get & print
    ft = scm_freetop();
    printf("%x\n\r", ft);

    // delay
    scm_delay(1000);
    
    // set
    scm_setfreetop(0xFBFF);

    // get & print
    ft = scm_freetop();
    printf("%x\n\r", ft);

    char c = scm_getc();
    scm_putc(c);
    scm_putc('\n');
    scm_putc('\r');

    char ch;
    for(f=0; f<255; f++) {
        scm_putc('.');
        scm_delay(100);
        ch = scm_aget();
        if(ch) break;
    }

    c = scm_getc();
    scm_putc(c);
    scm_putc('\n');
    scm_putc('\r');

    printf("Test end!\n\r");

    return 0;
}
