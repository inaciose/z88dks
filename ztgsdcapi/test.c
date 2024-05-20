//
// ZTGSDC file system calls api
//
// v0.01  - fexist, mkdir, rmdir, cd, cwd
//          fopen, fclose, fwrite, fread, ftell, frewind & fpeek
// v0.02  - seekset, seekcur, seekend
// v0.03  - all operations on the ztg rom v1.06p 

#include <stdio.h>

#include "ztgsdcapi.h"

char dirname1str[13] = {0};
char dirname2str[13] = {0};
char filename1str[13] = {0};
char filename2str[13] = {0};

int fhdl = 0;
int fhdl1 = 0;
int fhdl2 = 0;

int t_ren(char *src, char *dst);
int t_copy(char *src, char *dst);
int t_fdel(void);
int t_fexist(char *name);
int t_mkdir(void);
int t_rmdir(void);
int t_cd(char *s);
int t_cwd(void);

int t_slist(char *name);
int t_clist(void) ;

int t_fopen(char *s);
int t_fclose(int handle);

int t_fwrite(int hdl, char b);
int t_fwriteb(int hdl);
int t_fread(int hdl);
int t_freadb(int hdl);

int t_ftell(int hdl);
int t_fseekset(int hdl, unsigned long int pos);
int t_fseekcur(int hdl, long int pos);
int t_fseekend(int hdl, long int pos);
int t_frewind(int hdl);
int t_fpeek(int hdl);
int t_ftruncate(int hdl, unsigned long int pos);
int t_fgetsize(int hdl);
int t_fgetname(int hdl);
int t_lsof(void);

int t_sdifs(void);
int t_reset(void);

int t_fload(char *name);
int t_fsave(char *name);

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
    itmp = t_fexist(dirname1str);

    // 0 = not found
    if(itmp) {
        return 1;
    }

    // name not exists
    // make the new directory
    itmp = t_mkdir();

    //check if exists
    itmp = t_fexist(dirname1str);

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
    itmp = t_fexist(dirname1str);

    // 0 = not found
    if(itmp) {
        return 1;
    }

    // name not exists
    // make the new directory
    itmp = t_mkdir();

    //check if exists
    itmp = t_fexist(dirname1str);

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


    //check if exists
    itmp = t_fexist("wbytes");
    // 0 = not found
    if(itmp) {
        printf("remove wbytes file\n");
       return 1;
    }

     //check if exists
    itmp = t_fexist("sbytes");
    // 0 = not found
    if(itmp) {
        printf("remove sbytes file\n");
       return 1;
    }

    //check if exists
    itmp = t_fexist("truncated");
    // 0 = not found
    if(itmp) {
        printf("remove truncated file\n");
       return 1;
    }

    //check if exists
    itmp = t_fexist("renamed");
    // 0 = not found
    if(itmp) {
        printf("remove renamed file\n");
       return 1;
    }
    
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
        return -1;
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

    t_fseekcur(fhdl, -1);
    t_ftell(fhdl);

    t_fseekcur(fhdl, 2);
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

    t_copy(filename1str, "copied");
    t_copy(filename1str, "truncated");

        // open file name in read write create 0x0202
    itmp = t_fopen("truncated");

    // if itmp > 10, error, else handle id

    if(itmp && itmp < 11) {
        // not error
        // file is open with hdl itmp
        fhdl = itmp;

        printf("fopen handle: %x\n", itmp);


    } else {
        // error
        printf("fopen error: %x\n", itmp);
        return -1;
    }

    t_ftruncate(fhdl, 3);

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

    t_ren("copied", "renamed");

    t_lsof();

    fhdl = t_fopen(filename1str);
    //fhdl1 = t_fopen("copied");
    fhdl2 = t_fopen("truncated");

    t_lsof();

    t_fgetsize(fhdl);
    t_fgetname(fhdl);

    itmp = t_fclose(fhdl);
    //itmp = t_fclose(fhdl1);
    itmp = t_fclose(fhdl2);

    t_lsof();

    // delete file name
    itmp = t_fdel();

    itmp = t_sdifs();

    t_cd("fakefir");

    itmp = t_sdifs();

    t_reset();

    itmp = t_sdifs();

    // bof: list directory
    t_slist("");
    do {
        itmp = t_clist();
    } while(itmp);
    // eof

    t_lsof();

    fhdl = t_fopen("wbytes");
    t_fwriteb(fhdl);
    itmp = t_fclose(fhdl);

    t_lsof();

    fhdl = t_fopen("file.dat");
    t_freadb(fhdl);
    itmp = t_fclose(fhdl);

    t_lsof();

    // load file
    t_fload("wbytes");

    // save file
    t_fsave("sbytes");

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

int t_fwriteb(int hdl) {
    int itmp;

    char bytes2save[] = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvXxZz012345678";
    int bytes = 80;
    int nbytesproc;

    // we receive the file hdl id
    // as value (LSB)
    printf("t_fwriteb input: %x, %s, %x, %x, %x\n", hdl, bytes2save, &bytes2save, bytes, &nbytesproc); 

    // call api
    itmp = ztgsdc_fwriteb(hdl, (int) &bytes2save, bytes, (int*) &nbytesproc);

    // print
    printf("t_fwriteb: %x, %x\n", itmp, nbytesproc);

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

int t_freadb(int hdl) {
    int itmp;

    char bytesreaded[128] = {0};
    int bytes = 95;
    int nbytesproc;

    // we receive the file hdl id
    // as value (LSB)
    printf("t_readb input: %x, %s, %x, %x, %x\n", hdl, bytesreaded, &bytesreaded, bytes, &nbytesproc); 

    // call api
    itmp = ztgsdc_freadb(hdl, (int) &bytesreaded, bytes, (int*) &nbytesproc);

    // print
    printf("%s\n", bytesreaded);
    printf("t_readb: %x, %x\n", itmp, nbytesproc);

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
    printf("t_ftell: %lx\n", itmp);

    return itmp;
}

int t_fseekset(int hdl, unsigned long int pos) {

    int itmp;
    //unsigned long int pos = 0xDEADBEEFLU;
    //unsigned long int pos = 0x1;
    //printf(" %lx\n", pos);

    // we receive the file hdl id
    // as value (LSB)
    printf("t_fseekset input: %x, %lx\n", hdl, pos); 

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
    printf("t_fseekcur input: %x, %lx\n", hdl, pos); 

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
    printf("t_fseekend input: %x, %lx\n", hdl, pos); 

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

int t_ftruncate(int hdl, unsigned long int pos) {

    int itmp;
    //unsigned long int pos = 0xDEADBEEFLU;
    //unsigned long int pos = 0x1;
    //printf(" %lx\n", pos);

    // we receive the file hdl id
    // as value (LSB)
    printf("t_ftruncate input: %x, %lx\n", hdl, pos); 

    // close the file
    itmp = ztgsdc_ftruncate(hdl, &pos);

    // print
    printf("t_ftruncate: %x\n", (unsigned char) itmp);

    return itmp;
}

int t_fgetsize(int hdl) {

    unsigned long itmp;

    // we receive the file hdl id
    // as value (LSB)
    printf("t_fgetsize input: %x\n", hdl); 

    // close the file
    itmp = ztgsdc_fgetsize(hdl);

    // print
    printf("t_fgetsize: %lx\n", itmp);

    return itmp;
}

int t_fgetname(int hdl) {

    int itmp;

    char fname[32] = {0};

    // we already have a name
    // in a string var 
    // (char *, null terminated)

    // make directory
    itmp = ztgsdc_fgetname(hdl, fname);

    // print
    printf("name: %s\n", fname);
    printf("fgetname: %d\n", itmp);

    return itmp;
}

int t_lsof(void) {

    int itmp;
    int f;

    unsigned char cwdname[11] = {0};

    // we already have a name
    // in a string var 
    // (char *, null terminated)

    // get open files handles
    itmp = ztgsdc_lsof(cwdname);

    // print files open
    for(f=0; f<10; f++) {
        printf("lsof: %x ", cwdname[f]);
        if(!cwdname[f]) break;
    }
    printf("\n");
    
    printf("t_lsof: %d\n", itmp);

    return itmp;

}


int t_slist(char *name) {
    int itmp;

    // we already have a name
    // in a string var 
    // (char *, null terminated)

    // check if file, dir, name exist
    itmp = ztgsdc_slist(name);

    // print
    printf("t_slist: %x\n", itmp);

    return itmp;
}

int t_clist(void) {

    int itmp;

    char name[32] = {0};

    // we need to send an
    // address to store
    // the returned string var 
    // (char *, null terminated)

    // get dirctory item name
    itmp = ztgsdc_clist(name);

    // print
    printf("lname: %s\n", name);
    printf("t_clist: %d\n", itmp);

    if(name[0]) {
        return 1;
    } else {
        return 0;
    }

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

    // we need to send an
    // address to store
    // the returned string var 
    // (char *, null terminated)

    // get current directory name
    itmp = ztgsdc_cwd(cwdname);

    // print
    printf("cwd: %s\n", cwdname);
    printf("t_cwd: %d\n", itmp);

    return itmp;

}

int t_fexist(char *name) {
    int itmp;

    // we already have a name
    // in a string var 
    // (char *, null terminated)

    // check if file, dir, name exist
    itmp = ztgsdc_fexist(name);

    // print
    printf("t_fexist: %d\n", itmp);

    return itmp;
}

int t_fdel(void) {
    int itmp;

    // we already have a name
    // in a string var 
    // (char *, null terminated)

    // check if file, dir, name exist
    itmp = ztgsdc_fdel(filename1str);

    // print
    printf("t_fdel: %x\n", itmp);

    return itmp;
}

int t_ren(char *src, char *dst) {
    int itmp;

    // we already have a name
    // in a string var 
    // (char *, null terminated)

    // check if file, dir, name exist
    itmp = ztgsdc_fren(src, dst);

    // print
    printf("t_ren: %d\n", itmp);

    return itmp;
}

int t_copy(char *src, char *dst) {
    int itmp;

    // we already have a name
    // in a string var 
    // (char *, null terminated)

    // check if file, dir, name exist
    itmp = ztgsdc_fcopy(src, dst);

    // print
    printf("t_copy: %d\n", itmp);

    return itmp;
}

int t_sdifs(void) {

    int itmp;

    // close the file
    itmp = ztgsdc_sdifs();

    // print
    printf("t_sdifs: %x\n", itmp);

    return itmp;
}

int t_reset(void) {

    int itmp;

    // call the api
    itmp = ztgsdc_reset();

    // print
    printf("t_reset: %x\n", itmp);

    return itmp;
}


int t_fload(char *name) {
    int itmp;

    // we already have a name
    // in a string var 
    // (char *, null terminated)

    unsigned int dst_start = 0xE000;

    // print
    printf("t_fload input: %s, %x\n", name, dst_start);

    // check if file, dir, name exist
    itmp = ztgsdc_fload(name, dst_start);

    // print
    printf("t_fload: %x\n", itmp);

    return itmp;
}

int t_fsave(char *name) {
    //int itmp;

    // we already have a name
    // in a string var 
    // (char *, null terminated)

    unsigned int src_start = 0xE000;
    int src_len = 0x000f;

    // print
    printf("t_fsave input: %s, %x, %x\n", name, src_start, src_len);

    // call api
    ztgsdc_fsave(name, src_start, src_len);

    // print
    printf("t_fsave done\n");

    return 0;
}