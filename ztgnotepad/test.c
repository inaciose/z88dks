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

#define DEFAULT_LIN 7


int lin = DEFAULT_LIN;
int col = 1;
int idx = 0;

char text[TEXT_MAXLEN] = {0};
char line[LINE_MAXLEN] = {0};

extern int ztgsdcard_load(char *s, int start);
extern void ztgsdcard_save(char *s, int start, int len);

void ansicursor(int l, int c);
void setup(void);
void menuprint(int l, int c);
void printlincol(int l, int c);
void newFile(void);
void loadFile(void);
void saveFile(void);

void ansicursor(int l, int c)
{
    printf("%c[%d;%df",0x1B,l,c);
}

void setup(void) {
        printf(ANSIQ_SCR_CLR_ALL ANSIQ_CUR_HOME);
        menuprint(1, 1);
        lin = DEFAULT_LIN;
        col = 1;
        ansicursor(lin, col);
}

void menuprint(int l, int c) {
    ansicursor(l, c);
    printf(NAME_COLOR "Notepad " DEFAULT_COLOR " | Menu: " NAME_COLOR "\\m");
    printf(DEFAULT_COLOR " | " MENU_COLOR1 "1. New ");
    printf(DEFAULT_COLOR " | " MENU_COLOR1 "2. Load ");
    printf(DEFAULT_COLOR " | " MENU_COLOR1 "3. Save ");
    printf(DEFAULT_COLOR " | " MENU_COLOR1 "0. Exit "DEFAULT_COLOR);
    printf(ANSIQ_GR_RESET);
}

void printlincol(int l, int c) {
    ansicursor(l, c);
    printf(" | %x, %x", text, idx);
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
    char fnstr[13] = {0};
    int f;

    ansicursor(2, 1);
    printf("Load file: ");
    
    scanf("%12s", fnstr);
    //fgets(fnstr, 12, stdin);

    newFile();
    idx = ztgsdcard_load(fnstr, (int)text);

    ansicursor(lin+5, col);
    for(f=0; f < idx; f++) {
        putchar(*(text + f));
    }
    ansicursor(lin, col);
}

void saveFile(void) {
    char fnstr[13] = {0};
    
    ansicursor(2, 1);
    printf("save to file: ");

    scanf("%12s", fnstr);
    //fgets(fnstr, 12, stdin);

    ztgsdcard_save(fnstr, (int)text, idx);
    ansicursor(lin, col);
}



int main(void) {
    int choice = 10;
    int linelen = 0;
    int f;

    char c;

    setup();
    idx = 0;
    
    do {
        printlincol(1, 80);

        //scanf("%80[^\n]s", &line);
        fgets(line, LINE_MAXLEN - 1, stdin);

        // check for commands
        f = 0;
        if(line[0] == '\\'){
            if(line[1] == 'm') {
                //choice = getchoice();
                //continue;
                if(line[2] == '0') {
                    choice = 0;
                    setup();
                    printf("Exiting the program...\n");
                    break;

                }
                if(line[2] == '1') {
                    newFile();
                    continue;
                }            
                if(line[2] == '2') {
                    loadFile();
                    continue;
                }            
                if(line[2] == '3') {
                    saveFile();
                    continue;
                }            
            }
        }

        // add to text
        f = 0;
        while(line[f] != '\n') {
            text[idx++] = line[f++];
            linelen++;
        }
        text[idx++] = '\n';
        text[idx++] = 0;

        ansicursor(lin, col);

        for (f=0; f < LINE_MAXLEN; f++) {
            putchar(' ');
        }

        // show text bellow
        ansicursor(lin+5, col);
        for(f=0; f < idx; f++) {
            putchar(*(text + f));
        }

        ansicursor(lin, col);


    } while (choice != 0);
    
    return 0;
}
