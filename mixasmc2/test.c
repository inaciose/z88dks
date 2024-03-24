#include <stdio.h>

char str[] = "string\n\r\0";

extern void mputc(char c);
extern char mgetc(void);
extern void mput2c(char c, char d);

extern int scm_freetop(void);
extern void scm_setfreetop(int top);
extern void scm_delay(int ms);
extern void mprintsrt(char *s);
 
int main(void)
{
   mputc('O');                // call to asm subroutine
   mputc('\n'); 
   mputc('\r'); 

   mprintsrt(str);

   char c = mgetc();
   mputc(c);
   mputc('\n'); 
   mputc('\r');

   int ft = scm_freetop();
   printf("%x", ft);

   mputc('\n'); 
   mputc('\r');

   scm_setfreetop(0xFBAB);

   ft = scm_freetop();
   printf("%x\n\r", ft);

   scm_delay(1000);

   scm_setfreetop(0xFBFF);

   ft = scm_freetop();
   printf("%x\n\r", ft);

   mputc('\n'); 
   mputc('\r');

   mputc('k'); 
   mputc('\n'); 
   mputc('\r'); 

   c = mgetc();
   mputc(c);
   mputc('\n'); 
   mputc('\r'); 

   mputc('-'); 
   mput2c('A', 'c'); 

   mputc('\n'); 
   mputc('\r'); 
   return 0;
}
