#include <stdio.h>

#include "ansiq.h"

//
// colors
//
#define DEFAULT_COLOR ANSIQ_SETFG_WHITE
//#define SEP_COLOR ANSIQ_SETFG_WHITE

#define NAME_COLOR ANSIQ_SETFG_BLUE

#define MENU_COLOR1 ANSIQ_SETFG_GREEN
#define MENU_COLOR2 ANSIQ_SETFG_BLUE

//
// Chars
//
#define CTLC 0x03
#define BS 0x08
#define TAB 0x09
#define LF 0x0A
#define CR 0x0D
#define ESC 0x1b
#define DEL 0x7F

// Text

//#define MAXLINE 25
#define MAXCOL 80

#define LINE_MAXLEN MAXCOL
#define TEXT_MAXLEN 1024


int lin = 1;
int col = 1;
int idx = 0;

char text[TEXT_MAXLEN] = {0};
char line[LINE_MAXLEN] = {0};

extern int ztgsdcard_load(char *s, int start);
extern void ztgsdcard_save(char *s, int start, int len);

void setup(void);
void menuprint(int l, int c);


void ansicursor(int l, int c)
{
    printf("%c[%d;%df",0x1B,l,c);
}

void setup(void) {
        printf(ANSIQ_SCR_CLR_ALL ANSIQ_CUR_HOME);
        menuprint(1, 1);
        lin = 3;
        col = 1;
        ansicursor(lin, col);
}

void newFile(void) {
    printf("Creating a new file...\n");
    // Add your code here to handle creating a new file
    int f;

    for(f = 0; f < LINE_MAXLEN; f++) {
        line[f] = 0;
    }

    for(f = 0; f < idx; f++) {
        text[f] = 0;
    }

    idx = 0;

    setup();

}

void loadFile(void) {

    //char *ptr = text;
    char fnstr[13] = {0};
    int f;

    ansicursor(2, 1);
    printf("Load file: ");
    scanf("%12s", fnstr);
    newFile();

    idx = ztgsdcard_load(fnstr, (int)text);

    ansicursor(lin+20, col);
    for(f=0; f < idx; f++) {
        putchar(*(text + f));
    }
    ansicursor(3, 1);
}

void saveFile(void) {
    char fnstr[13] = {0};
    ansicursor(2, 1);
    printf("save to file: ");
    scanf("%12s", fnstr);
    ztgsdcard_save(fnstr, (int)text, idx);
}

void closeFile(void) {
    printf("Closing the file...\n");
    // Add your code here to handle closing the file
}

void menuprint(int l, int c) {
    ansicursor(l, c);
    printf(NAME_COLOR "Notepad Menu");
    printf(DEFAULT_COLOR " | " MENU_COLOR1 "1. New ");
    printf(DEFAULT_COLOR " | " MENU_COLOR1 "2. Load ");
    printf(DEFAULT_COLOR " | " MENU_COLOR1 "3. Save ");
    //printf(DEFAULT_COLOR " | " MENU_COLOR1 "4. Close ");
    printf(DEFAULT_COLOR " | " MENU_COLOR1 "5. Exit "DEFAULT_COLOR " | ");
    printf(ANSIQ_GR_RESET);

}

int getchoice(void) {
    int choice;

    menuprint(1, 1);
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            newFile();
            break;
        case 2:
            loadFile();
            break;
        case 3:
            saveFile();
            break;
        case 4:
            closeFile();
            break;
        case 5:
            printf("Exiting the program...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
    }
    
    printf("\n");


    return choice;
}

void printlincol(int l, int c) {
    ansicursor(1, 84);
    printf("%d, %d", l, c);
    printf(" | %x %x, %x", &idx, text, idx);
    ansicursor(l, c);
}


int main(void) {
    int choice = 0;
    int linelen = 0;
    int f;

    char c;

    char *ptr = text;

    setup();
    idx = 0;
    
    do {
        printlincol(lin, col);

        scanf("%80s", &line);

        // check for commands
        f = 0;
        if(line[0] == '\\'){
            if(line[1] == 'm') {
                choice = getchoice();
                continue;
            }
        }

        // add to text
        f = 0;
        while(line[f] != 0) {
            text[idx++] = line[f++];
        }
        text[idx++] = 0;

        lin++;
        col=0;

        ansicursor(lin+20, col);
        for(f=0; f < idx; f++) {
            putchar(*(ptr + f));
        }

        ansicursor(lin, col);


    } while (choice != 5);
    
    return 0;
}
