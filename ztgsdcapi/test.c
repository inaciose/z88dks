//
// ZTGSDC file system calls api
//
// v0.01  - fexist, mkdir, rmdir, cd, cwd
//          fopen, fclose, fwrite, fread, ftell, frewind & fpeek
// v0.02  - seekset, seekcur, seekend

#include <stdio.h>

char dirname1str[13] = {0};
char dirname2str[13] = {0};
char filename1str[13] = {0};
char filename2str[13] = {0};

int fhdl = 0;


extern int ztgsdc_fexist(char *s);
extern int ztgsdc_mkdir(char *s);
extern int ztgsdc_rmdir(char *s);
extern int ztgsdc_cd(char *s);
extern int ztgsdc_cwd(char *s);

extern int ztgsdc_fopen(char *s, int mode);
extern int ztgsdc_fclose(int handle);

extern int ztgsdc_fwrite(int handle, int b);
extern int ztgsdc_fread(int handle, int *res);
extern unsigned long int ztgsdc_ftell(int handle);

extern int ztgsdc_frewind(int handle);
extern int ztgsdc_fpeek(int handle);

extern int ztgsdc_fseekset(int handle, unsigned long int *pos);
extern int ztgsdc_fseekcur(int handle, long int *pos);
extern int ztgsdc_fseekend(int handle, long int *pos);

int t_fexist(void);
int t_mkdir(void);
int t_rmdir(void);
int t_cd(char *s);
int t_cwd(void);

int t_fopen(char *s);
int t_fclose(int handle);

int t_fwrite(int hdl, char b);
int t_fread(int hdl);

int t_ftell(int hdl);
int t_fseekset(int hdl, unsigned long int pos);
int t_fseekcur(int hdl, long int pos);
int t_fseekend(int hdl, long int pos);

int t_frewind(int hdl);
int t_fpeek(int hdl);

int main(void) {

    int itmp;

/*
    //
    // fexist, mkdir & rmdir tests
    //

    // ask for directory name
    printf("Insert directory name: ");
    scanf("%12s", dirname1str);

    //check if exists
    itmp = t_fexist();

    // 0 = not found
    if(itmp) {
        return 1;
    }

    // name not exists
    // make the new directory
    itmp = t_mkdir();

    //check if exists
    itmp = t_fexist();

    // 0 = not found
    if(!itmp) {
        return 1;
    }

    // name exists
    // remove directory
    itmp = t_rmdir();

    //
    // repeat the directory
    // creation to go on
    //

    //check if exists
    itmp = t_fexist();

    // 0 = not found
    if(itmp) {
        return 1;
    }

    // name not exists
    // make the new directory
    itmp = t_mkdir();

    //check if exists
    itmp = t_fexist();

    // 0 = not found
    if(!itmp) {
        return 1;
    }

    //
    // cd & cwd tests
    //

    // cwd: get current workind directory name
    t_cwd();

    // change to the new directory name
    t_cd(dirname1str);

    // cwd: get current workind directory name
    t_cwd();

    // change to root
    t_cd("/");

*/

    //
    // fopen & fclose tests
    //

    // ask for directory name
    printf("Insert file name: ");
    scanf("%12s", filename1str);

    // open file name in read write create 0x0202
    itmp = t_fopen(filename1str);

    // if itmp > 10, error, else handle id

    if(itmp && itmp < 11) {
        // not error
        // file is open with hdl itmp
        fhdl = itmp;

        printf("fopen handle: %x\n", itmp);


    } else {
        // error
        printf("fopen error: %x\n", itmp);
    }

    itmp = t_fwrite(fhdl, 'h');
    itmp = t_fwrite(fhdl, 'e');
    itmp = t_fwrite(fhdl, 'l');
    itmp = t_fwrite(fhdl, 'l');
    itmp = t_fwrite(fhdl, 'o');
    itmp = t_fwrite(fhdl, '!');


    printf("rewind to begin of file\n");

    itmp = t_frewind(fhdl);

    printf("Write H to begin\n");
    itmp = t_fwrite(fhdl, 'H');

    printf("rewind to begin of file\n");
    itmp = t_frewind(fhdl);

    itmp = t_fpeek(fhdl);
    itmp = t_fpeek(fhdl);
    itmp = t_fread(fhdl);

    itmp = t_fpeek(fhdl);
    itmp = t_fpeek(fhdl);
    itmp = t_fread(fhdl);

    itmp = t_fread(fhdl);

    itmp = t_fread(fhdl);

    itmp = t_fread(fhdl);
    t_ftell(fhdl);

    itmp = t_fread(fhdl);
    t_ftell(fhdl);

    itmp = t_fread(fhdl);
    t_ftell(fhdl);

    itmp = t_fread(fhdl);
    t_ftell(fhdl);

    t_fseekset(fhdl, 1);
    t_ftell(fhdl);

    t_fseekset(fhdl, 3);
    t_ftell(fhdl);

    t_fseekcur(fhdl, -3);
    t_ftell(fhdl);

    t_fseekcur(fhdl, 5);
    t_ftell(fhdl);

    itmp = t_fpeek(fhdl);
    t_ftell(fhdl);

    t_fseekend(fhdl, -3);
    t_ftell(fhdl);

    t_fseekend(fhdl, -4);
    t_ftell(fhdl);

    // close file
    if(fhdl) {
        // close the file
        itmp = t_fclose(fhdl);

        if(!itmp) {
            printf("file closed\n");
        } else {
            printf("error on file close\n");
        }    
    }

    return 0;

}

int t_fopen(char *name) {

    int itmp;

    // we receive the destination
    // name string address as pointer
    // (char *, null terminated)

    // open file name in read write create 0x0202
    itmp = ztgsdc_fopen(name, 0x0202);

    // print
    printf("t_fopen: %x\n", itmp);

    return itmp;

}

int t_fclose(int hdl) {

    int itmp;

    // we receive the file hdl id
    // as value (LSB)
    printf("t_fclose input: %x\n", hdl); 

    // close the file
    itmp = ztgsdc_fclose(hdl);

    // print
    printf("t_fclose: %x\n", itmp);

    return itmp;
}

int t_fwrite(int hdl, char b) {

    int itmp;

    // we receive the file hdl id
    // as value (LSB)
    printf("t_fwrite input: %x, %x\n", hdl, b); 

    // write a byte (LSB of int16) to  the file
    itmp = ztgsdc_fwrite(hdl, (int) b);

    // print
    printf("t_fwrite: %c, %x\n", b, (unsigned char) itmp);

    return itmp;
}

int t_fread(int hdl) {

    int itmp;

    // this store the
    // operation result
    unsigned char res = 0;

    // we receive the file hdl id
    // as value (LSB)
    printf("t_fread input: %x\n", hdl); 

    // write a byte (LSB of int16) to  the file
    itmp = ztgsdc_fread(hdl, &res);

    // itmp have the byte readed
    // res have the operation result byte

    // print
    printf("t_fread: %c, %x, %x\n", (char)itmp, (char)itmp, res);

    return itmp;
}

int t_ftell(int hdl) {

    unsigned long itmp;

    // we receive the file hdl id
    // as value (LSB)
    printf("t_ftell input: %x\n", hdl); 

    // close the file
    itmp = ztgsdc_ftell(hdl);

    // print
    printf("t_ftell: %x\n", itmp);

    return itmp;
}

int t_fseekset(int hdl, unsigned long int pos) {

    int itmp;
    //unsigned long int pos = 0xDEADBEEFLU;
    //unsigned long int pos = 0x1;
    printf("%lx\n", pos);

    // we receive the file hdl id
    // as value (LSB)
    printf("t_fseekset input: %x\n", hdl); 

    // close the file
    itmp = ztgsdc_fseekset(hdl, &pos);

    // print
    printf("t_fseekset: %x\n", (unsigned char) itmp);

    return itmp;
}

int t_fseekcur(int hdl, long int pos) {

    int itmp;
    //long int pos = 0xDEADBEEFLU;
    //long int pos = 0x1;
    printf("%lx\n", pos);

    // we receive the file hdl id
    // as value (LSB)
    printf("t_fseekcur input: %x\n", hdl); 

    // close the file
    itmp = ztgsdc_fseekcur(hdl, &pos);

    // print
    printf("t_fseekcur: %x\n", (unsigned char) itmp);

    return itmp;
}

int t_fseekend(int hdl, long int pos) {

    int itmp;
    //long int pos = 0xDEADBEEFLU;
    //long int pos = 0x1;
    printf("%lx\n", pos);

    // we receive the file hdl id
    // as value (LSB)
    printf("t_fseekend input: %x\n", hdl); 

    // call
    itmp = ztgsdc_fseekend(hdl, &pos);

    // print
    printf("t_fseekend: %x\n", (unsigned char) itmp);

    return itmp;
}


int t_frewind(int hdl) {

    int itmp;

    // we receive the file hdl id
    // as value (LSB)
    printf("t_frewind input: %x\n", hdl); 

    // close the file
    itmp = ztgsdc_frewind(hdl);

    // print
    printf("t_frewind: %x\n", itmp);

    return itmp;
}

int t_fpeek(int hdl) {

    int itmp;

    // we receive the file hdl id
    // as value (LSB)
    printf("t_fpeek input: %x\n", hdl); 

    // close the file
    itmp = ztgsdc_fpeek(hdl);

    // print
    printf("t_fpeek: %c, %x\n", (char) itmp, (unsigned char) itmp);

    return itmp;
}


int t_mkdir(void) {

    int itmp;

    // we already have a name
    // in a string var 
    // (char *, null terminated)

    // make directory
    itmp = ztgsdc_mkdir(dirname1str);

    // print
    printf("t_mkdir: %d\n", itmp);

    return itmp;

}

int t_rmdir(void) {

    int itmp;

    // we already have a name
    // in a string var 
    // (char *, null terminated)

    // make directory
    itmp = ztgsdc_rmdir(dirname1str);

    // print
    printf("t_rmdir: %d\n", itmp);

    return itmp;
}

int t_cd(char *name) {

    int itmp;

    // we receive the destination
    // name string address as pointer
    // (char *, null terminated)

    // change directory
    itmp = ztgsdc_cd(name);

    // print
    printf("t_cd: %d\n", itmp);

    return itmp;
}

int t_cwd(void) {

    int itmp;

    char cwdname[32] = {0};

    // we already have a name
    // in a string var 
    // (char *, null terminated)

    // make directory
    itmp = ztgsdc_cwd(cwdname);

    // print
    printf("cwd: %s\n", cwdname);
    printf("t_cwd: %d\n", itmp);

    return itmp;

}

int t_fexist(void) {
    int itmp;

    // we already have a name
    // in a string var 
    // (char *, null terminated)

    // check if file, dir, name exist
    itmp = ztgsdc_fexist(dirname1str);

    // print
    printf("t_fexist: %d\n", itmp);

    return itmp;
}
