#include <stdio.h>

int main()
{
    printf("Hello World !\n\r");
    while ( 1 ) {
        int c = getchar();
        printf("<%c>=%d ", c,c);
        if(c=='q') break;
    }
    return 0;
}
