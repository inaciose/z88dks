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

/*
int main()
{
    printf("Hello World !\n\r");
    return 0;
}


int main()
{
    int c;
    putchar('x');
    putchar('S');
    putchar('I');
    while ( 1 ) {
        c = getchar();
        putchar(c);
    }
    return 0;
}
*/