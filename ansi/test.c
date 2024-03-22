#include <stdio.h>
#include "ansiq_screen.h"
#include "ansiq_cursor.h"
#include "ansiq_graphics.h"

int main(void){
    // clear all and go home
    printf(ANSIQ_SCR_CLR_ALL ANSIQ_CUR_HOME);

    // ANSIQ_SETBG_RGB(r, g, b)
    printf(ANSIQ_SETBG_RGB(0, 0, 0));

    printf(ANSIQ_SETFG_GREEN"Hello, world!"ANSIQ_GR_RESET"\n");

    // ANSIQ_CUR_SET(l, c)
    // home (1,1)
    // printf(ANSIQ_CUR_SET(4, 0) ANSIQ_SETFG_RED "Hello, world!" ANSIQ_GR_RESET "\n");
    printf(ANSIQ_CUR_SET(3, 1) ANSIQ_SETFG_CYAN "Hello, world!" ANSIQ_GR_RESET "\n");
    printf(ANSIQ_CUR_SET(4, 2) ANSIQ_SETFG_GREEN "Hello, world!" ANSIQ_GR_RESET "\n");
    printf(ANSIQ_CUR_SET(5, 5) ANSIQ_SETFG_BLUE "Hello, world!" ANSIQ_GR_RESET "\n");

    // ANSIQ_SETBG_RGB(r, g, b)
    //printf(ANSIQ_SETBG_RGB(255, 0, 0));

    // need enter
    //int c=getchar();

    printf(ANSIQ_SETFG_GREEN);
    
    printf(ANSIQ_CUR_DOWN(1) "X");
    printf(ANSIQ_CUR_DOWN(1) "X");
    printf(ANSIQ_CUR_RIGHT(1) "X");
    printf(ANSIQ_CUR_RIGHT(1) "X");
    printf(ANSIQ_CUR_RIGHT(1) "X");
    printf(ANSIQ_CUR_UP(1) "X");
    printf(ANSIQ_CUR_RIGHT(1) "X");
    printf(ANSIQ_CUR_RIGHT(1) "X");
    printf(ANSIQ_CUR_DOWN(1) "X");
    printf(ANSIQ_CUR_DOWN(1) "X");
    printf(ANSIQ_CUR_RIGHT(1) "X");
    printf(ANSIQ_CUR_DOWN(1) "X");
    printf(ANSIQ_CUR_DOWN(1) "X");
    printf(ANSIQ_CUR_DOWN(1) "X");
    printf(ANSIQ_CUR_LEFT(1) "X");
    printf(ANSIQ_CUR_DOWN(1) "X");
    printf(ANSIQ_CUR_LEFT(1) "X");
    printf(ANSIQ_CUR_LEFT(1) "X");
    printf(ANSIQ_CUR_LEFT(1) "X");

    printf(ANSIQ_GR_RESET);


    //printf(ANSIQ_CUR_SET(8, 1) ANSIQ_SETFG_CYAN "Hello, world!" ANSIQ_GR_RESET "\n");
    //printf(ANSIQ_CUR_SET(24, 40) ANSIQ_SETFG_GREEN "Hello, world!" ANSIQ_GR_RESET "\n");
    //printf(ANSIQ_CUR_SET(30, 80) ANSIQ_SETFG_BLUE "Hello, world!" ANSIQ_GR_RESET "\n");

    printf("\n\r");

    return 0;
}
