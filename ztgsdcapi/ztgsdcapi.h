#ifndef ZTGSDCAPI_H
#define ZTGSDCAPI_H


extern int ztgsdc_fcopy(char *s, char *d);
extern int ztgsdc_fren(char *s, char *d);
extern int ztgsdc_fdel(char *s);
extern int ztgsdc_fexist(char *s);
extern int ztgsdc_mkdir(char *s);
extern int ztgsdc_rmdir(char *s);
extern int ztgsdc_cd(char *s);
extern int ztgsdc_cwd(char *s);

extern int ztgsdc_slist(char *s);
extern int ztgsdc_clist(char *s);

extern int ztgsdc_fopen(char *s, int mode);
extern int ztgsdc_fclose(int handle);

extern int ztgsdc_fwrite(int handle, int b);
extern int ztgsdc_fwriteb(int handle, int start, int bytes, int *nbytes); 
extern int ztgsdc_fread(int handle, int *res);
extern int ztgsdc_freadb(int handle, int start, int bytes, int *nbytes);

extern int ztgsdc_fpeek(int handle);
extern unsigned long int ztgsdc_ftell(int handle);

extern int ztgsdc_fseekset(int handle, unsigned long int *pos);
extern int ztgsdc_fseekcur(int handle, long int *pos);
extern int ztgsdc_fseekend(int handle, long int *pos);
extern int ztgsdc_frewind(int handle);
extern int ztgsdc_ftruncate(int handle, unsigned long int *pos);
extern unsigned long int ztgsdc_fgetsize(int handle);
extern int ztgsdc_fgetname(int handle, char *s);
extern int ztgsdc_lsof(char *s);

extern int ztgsdc_sdifs(void);
extern int ztgsdc_reset(void);

extern void ztgsdc_fsave(char *s, int start, int len);
extern int ztgsdc_fload(char *s, int start);

extern unsigned long int ztgsdc_fdspace(void);
extern unsigned long int ztgsdc_tdspace(void);

#endif
