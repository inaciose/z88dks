#include <stdio.h>
 
int a[5] = {0,1,2,3,4};
 
void negate_odd_a(void)
{
   int i;
 
   for (i=0; i!=5; ++i)
      if (a[i] & 0x01) a[i] = -a[i];          // negate odd numbers in array a[]
 
   return;
}
 
extern void neg_and_triple_a(void);   // implemented elsewhere
 
int main(void)
{
   int i;
 
   neg_and_triple_a();                // call to asm subroutine
 
   for (i=0; i!=5; ++i)
      printf("a[%d]=%d\n", i, a[i]);
 
   return 0;
}
