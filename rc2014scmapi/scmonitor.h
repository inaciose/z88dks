#ifndef _SCMONITOR_H_
#define _SCMONITOR_H_

extern char scm_getc(void);
extern void scm_putc(char c);
extern char scm_agetc(void);
extern void scm_printline(char *s);
extern void scm_delay(int ms);
extern int scm_freetop(void);
extern void scm_setfreetop(int top);

#endif