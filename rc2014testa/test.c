#include <stdio.h>

int main()
{
    printf("Hello World !\n");
    while ( 1 ) {
        int c = getchar();
        printf("<%c>=%d ", c,c);
    }
    return 0;
}

