#include <stdio.h>
#include "ansiq_screen.h"
#include "ansiq_cursor.h"
#include "ansiq_graphics.h"

extern char scm_agetc(void);
extern char scm_getc(void);

unsigned int xorshift128(void);
void new_apple(void);
void update_score(void);
void initialize(void);
int update_snake(void);

#define FIELD_CHAR 'F'
#define FIELD_W 78
#define FIELD_H 40
#define LOOP_DELAY 5000
#define SCORE_PER_APPLE 10

// colors
#define FIELD_COLOR ANSIQ_SETBG_BLUE
#define BG_COLOR    ANSIQ_SETBG_BLACK
#define APPLE_COLOR ANSIQ_SETBG_RED
#define SNAKE_COLOR ANSIQ_SETBG_GREEN

unsigned char field[FIELD_W * FIELD_H];
struct {
    int i;
    int j;
} snake_head;

struct {
    int i;
    int j;
} snake_tail;

// pseudo random
unsigned int score;
unsigned int rnd_x = 4;
unsigned int rnd_y = 113;
unsigned int rnd_z = 543;
unsigned int rnd_w = 11;

void ansicursor(int l, int c)
{
    printf("%c[%d;%df",0x1B,l,c);
}

int main(void){

    char usercommand;
    int  head_idx;

    // allow exit to scm
    int run = 1;

    initialize();

    // pseudo random
    while (getchar() != 'n')
        rnd_x++;

    /*
    while (scm_agetc() != 'n')
    {
        scm_getc();
        rnd_x++;
    }
    scm_getc();
    */

    while (run)
    {
        if (update_snake() == 0)
        {
            ansicursor(FIELD_H / 2, FIELD_W / 2 - 5);
            printf("GAME OVER!");
            
            // wait command for new game           
            while (scm_getc() != 'n') ;
            initialize();
            continue;
        }

        usercommand = 0; // none
        //usercommand = rc2014_inp(0x01);

        if (scm_agetc())
        {
            usercommand = scm_getc();
        }

        head_idx = snake_head.i * FIELD_W + snake_head.j;

        switch(usercommand)
        {
            case 'w':
            case 'W':
            case 1:
                if (field[head_idx] != 'D')
                    field[head_idx] = 'U';
                break;

            case 'o':
            case 'O':
            case 8:
                if (field[head_idx] != 'L')
                    field[head_idx] = 'R';
                break;

            case 'i':
            case 'I':
            case 4:
                if (field[head_idx] != 'R')
                    field[head_idx] = 'L';
                break;

            case 's':
            case 'S':
            case 2:
                if (field[head_idx] != 'U')
                    field[head_idx] = 'D';
                break;

            case 'n':
            case 'N':
                initialize();
                continue;

            case 'p':
            case 'P':
                while (1)
                  if (scm_agetc() && scm_getc() == 'p')
                      break;
                break;

            case 'x':
            case 'X':
                run = 0;
                break;

            case 0:
                // do nothing
                break;

            break;
        }

        // delay
        //scm_delay(500);
       
        // DELAY LOOP
#asm
        push af
        push bc
        ld BC, 0x5000 ;@ ~0.5 sec loop
DELY:   NOP
        DEC BC
        LD A,B
        OR C
        JP NZ, DELY

        pop bc
        pop af
#endasm

    }

    printf(ANSIQ_SCR_CLR_ALL ANSIQ_CUR_HOME);
    printf(ANSIQ_GR_RESET);
    printf("Snake say bye...\n\r");
    printf("\n\r");

    return 0;
}

//
// pesudo random generator
//
unsigned int xorshift128(void) {
    unsigned int t = rnd_x;
    t ^= t << 11;
    t ^= t >> 8;
    rnd_x = rnd_y;
    rnd_y = rnd_z;
    rnd_z = rnd_w;
    rnd_w ^= rnd_w >> 19;
    rnd_w ^= t;
    return rnd_w;
}

//
// creates and apple
//
void new_apple(void)
{
    unsigned int apple_i;
    unsigned int apple_j;
    unsigned int apple_idx;

    while (1)
    {
        apple_i = (xorshift128() % (FIELD_H - 3)) + 2;
        apple_j = (xorshift128() % (FIELD_H - 3)) + 2;

        apple_idx = apple_i * FIELD_W + apple_j;

        if (field[apple_idx] == 0)
        {
            field[apple_idx] = 'A';
            ansicursor(apple_i + 1, apple_j + 1);
            printf(ANSIQ_SETBG_RED);
            putchar(' ');
            return;
        }
    }
}

//
//
//
void update_score(void) {
  printf("SCORE: %d", score);
}

//
//
//
void initialize(void)
{
    int i;
    int j;
    int head_idx;
    int tail_idx;
    unsigned char* pfield = field;

    score = 0;

    //cant hide the cursor
    printf(ANSIQ_SCR_CLR_ALL ANSIQ_CUR_HOME);

    printf(FIELD_COLOR);
    // Top
    ansicursor(1, 1);

    pfield = field;

    for (i = 0; i < FIELD_W; ++i)
    {
        putchar(' ');
        *pfield++ = FIELD_CHAR;
    }

    // Left-Right
    for (i = 1; i < FIELD_H - 1; ++i)
    {
        printf(FIELD_COLOR);
        ansicursor(i + 1, 1);
        putchar(' ');
        *pfield++ = FIELD_CHAR;

        printf(BG_COLOR);
        for (j = 1; j < FIELD_W - 1; ++j)
        {
            putchar(' ');
            *pfield++ = 0;
        }

        printf(FIELD_COLOR);
        putchar(' ');
        *pfield++ = FIELD_CHAR;
    }

    // Bottom
    ansicursor(FIELD_H, 1);
    for (i = 0; i < FIELD_W; ++i)
    {
        putchar(' ');
        *pfield++ = FIELD_CHAR;
    }

    // Snake
    printf(SNAKE_COLOR);

    snake_head.i = FIELD_H / 2;
    snake_head.j = FIELD_W / 2;
    snake_tail.i = snake_head.i + 2;
    snake_tail.j = snake_head.j;
    head_idx = snake_head.i * FIELD_W + snake_head.j;
    field[head_idx] = 'U';
    field[head_idx+FIELD_W] = 'U';
    field[head_idx+FIELD_W+FIELD_W] = 'U';

    ansicursor(snake_head.i + 1, snake_head.j + 1);
    putchar(' ');
    ansicursor(snake_head.i + 2, snake_head.j + 1);
    putchar(' ');
    ansicursor(snake_head.i + 3, snake_head.j + 1);
    putchar(' ');

    new_apple();

    // Credits/Help
    printf(BG_COLOR);
    ansicursor(FIELD_H + 1, 1);
    printf(SNAKE_COLOR);
    printf("  *RC2014 SNAKE*  ");
    printf(BG_COLOR);
    printf("XSI 2024 based on work of F. B. 2016");
    ansicursor(FIELD_H + 2, 1);    
    printf("w:up, s:down, i:left, o:right, n:new game, p:pause, x:exit");
    ansicursor(FIELD_H + 1, 60);
    printf(APPLE_COLOR);
    update_score();
    printf(BG_COLOR);
}

//
//
//
int update_snake(void)
{
    int head_idx = snake_head.i * FIELD_W + snake_head.j;
    int tail_idx = snake_tail.i * FIELD_W + snake_tail.j;
    unsigned char c_head = field[head_idx];
    unsigned char keepsize = 1;

    switch(c_head)
    {
        case 'U':
            head_idx -= FIELD_W;
            snake_head.i--;
            break;

        case 'D':
            head_idx += FIELD_W;
            snake_head.i++;
            break;

        case 'L':
            head_idx--;
            snake_head.j--;
            break;

        case 'R':
            head_idx++;
            snake_head.j++;
            break;
    }

    if (field[head_idx] == 'A')
    {
        keepsize = 0;
        score += SCORE_PER_APPLE;
        printf(BG_COLOR);
        ansicursor(FIELD_H + 1, 60);
        update_score();
    }
    else
    {
        if (field[head_idx] != 0)
        {
            return 0;
        }
    }

    printf(SNAKE_COLOR);

    field[head_idx] = c_head;
    ansicursor(snake_head.i + 1, snake_head.j + 1);
    putchar(' ');

    if (keepsize)
    {
        c_head = field[tail_idx];
        field[tail_idx] = 0;

        printf(BG_COLOR);
        ansicursor(snake_tail.i + 1, snake_tail.j + 1);
        putchar(' ');

        switch(c_head)
        {
            case 'U':
                snake_tail.i--;
                break;

            case 'D':
                snake_tail.i++;
                break;

            case 'L':
                snake_tail.j--;
                break;

            case 'R':
                snake_tail.j++;
                break;
        }
    }
    else
    {
        new_apple();
    }

    return 1;
}
