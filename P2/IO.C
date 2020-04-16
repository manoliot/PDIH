#include "IO.H"
#include <dos.h>

byte THE_FG_COLOR = 15;
byte THE_BG_COLOR = 0;

void gotoxy(byte x, byte y)
{
	union REGS inregs, outregs;

	inregs.h.ah = 2;
	inregs.h.dh = x;
	inregs.h.dl = y;
	inregs.h.bh = 0;
	int86(0x10, &inregs, &outregs);
}

void setcursortype(CURSOR_TYPE type)
{
	union REGS inregs, outregs;

	inregs.h.ah = 0x01;
	switch(type) {
		case _NOCURSOR:
			inregs.h.ch = 010;
			inregs.h.cl = 000;
			break;
		case _NORMALCURSOR:
			inregs.h.ch = 010;
			inregs.h.cl = 010;
			break;
		case _SOLIDCURSOR:
			inregs.h.ch = 000;
			inregs.h.cl = 010;
			break;
	}
	int86(0x10, &inregs, &outregs);
}

void setvideomode(byte mode)
{
	union REGS inregs, outregs;

	inregs.h.ah = 0x0;
	inregs.h.al = mode;
	int86(0x10, &inregs, &outregs);
}

byte getvideomode(void)
{
	union REGS inregs, outregs;

	inregs.h.ah = 0xF;
	int86(0x10, &inregs, &outregs);
	return outregs.h.al;
}

void textcolor(byte color) {
	THE_FG_COLOR = color;
}

void textbackground(byte color)
{
	THE_BG_COLOR = color;
}

void clrscr(void)
{
	union REGS inregs, outregs;

	inregs.h.ah = 6;
	inregs.h.al = 0;
	inregs.h.bh = (THE_BG_COLOR << 4) | THE_FG_COLOR;
	inregs.h.ch = 0;
	inregs.h.cl = 0;
	inregs.h.dh = 25;
	inregs.h.dl = 80;
	int86(0x10, &inregs, &outregs);
}

void cputchar(char c)
{
	union REGS inregs, outregs;

	inregs.h.ah = 9;
	inregs.h.al = c;
	inregs.h.bl = (THE_BG_COLOR << 4) | THE_FG_COLOR;
	inregs.h.bh = 0;
	inregs.x.cx = 1;
	int86(0x10, &inregs, &outregs);
}

char getche(void)
{
	union REGS inregs, outregs;

	inregs.h.ah = 1;
	int86(0x21, &inregs, &outregs);

	return outregs.h.al;
}

char getch(void)
{
	union REGS inregs, outregs;

	inregs.h.ah = 0;
	int86(0x16, &inregs, &outregs);

	return outregs.h.al;
}

void drawrect(byte x0, byte y0, byte x1, byte y1, byte bg, byte fg)
{
	union REGS inregs, outregs;

	inregs.h.ah = 6;
	inregs.h.al = 0;
	inregs.h.bh = (bg << 4) | THE_FG_COLOR;
	inregs.h.ch = 0;
	inregs.h.cl = 0;
	inregs.h.dh = 25;
	inregs.h.dl = 80;
	int86(0x10, &inregs, &outregs);

	inregs.h.bh = (fg << 4) | THE_FG_COLOR;
	inregs.h.ch = y0;
	inregs.h.cl = x0;
	inregs.h.dh = y1;
	inregs.h.dl = x1;
	int86(0x10, &inregs, &outregs);
}

void drawpx(unsigned int x, unsigned int y, byte color)
{
	union REGS inregs, outregs;

	inregs.h.ah = 0x0C;
	inregs.h.al = color;
	inregs.x.cx = x;
	inregs.x.dx = y;
	int86(0x10, &inregs, &outregs);
}
