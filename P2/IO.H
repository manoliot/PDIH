#ifndef IO_H
#define IO_H

#define _TEXTMODE = 3
#define _GRAPHICMODE = 4
#define _VGAMODE = 13

typedef unsigned char byte;

typedef enum {
    _NOCURSOR,
    _NORMALCURSOR,
    _SOLIDCURSOR,
} CURSOR_TYPE;

void gotoxy(byte, byte);
void setcursortype(CURSOR_TYPE);
void setvideomode(byte);
byte getvideomode(void);
void textcolor(byte);
void textbackground(byte);
void clrscr(void);
void cputchar(char);
char getche(void);
char getch(void);

void drawrect(byte, byte, byte, byte, byte, byte);
void drawpx(unsigned int, unsigned int, byte);

#endif
