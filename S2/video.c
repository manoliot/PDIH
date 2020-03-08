#include <stdio.h>
#include <dos.h>

char my_getc() {
	union REGS inregs, outregs;

	inregs.h.ah = 8;
	int86(0x21, &inregs, &outregs);
	return outregs.h.al;
}

void change_video_mode(char mode) {
	union REGS inregs, outregs;

	inregs.h.ah = 0x00;
	inregs.h.al = mode;
	int86(0x10, &inregs, &outregs);
}

void draw_pixel(int x, int y, char color) {
	union REGS inregs, outregs;

	inregs.h.ah = 0x0C;
	inregs.h.al = color;
	inregs.x.cx = x;
	inregs.x.dx = y;
	int86(0x10, &inregs, &outregs);
}


int main() {
	int c, x, y;

	// Modo gráfico
	change_video_mode(4);

	// Rectángulo
	for(y=50; y<150; y++) {
		for(x=60; x<260; x++) {
			draw_pixel(x, y, 3);
		}
	}

	// Línea vertical
	x = 160;
	for(y=50; y<150; y++) {
		draw_pixel(x, y, 1);
	}


	// Línea horizontal
	y = 100;
	for(x=60; x<260; x++) {
		draw_pixel(x, y, 2);
	}

	// Pausa y modo 80x25
	c = my_getc();
	change_video_mode(3);

	return 0;
}
