#include <stdio.h>
#include <dos.h>

char my_getc() {
	union REGS inregs, outregs;

	inregs.h.ah = 8;
	int86(0x21, &inregs, &outregs);
	return outregs.h.al;
}

void my_putc(char c) {
	union REGS inregs, outregs;

	inregs.h.ah = 2;
	inregs.h.dl = c;
	int86(0x21, &inregs, &outregs);
}

int main() {
	int c;

	printf("Pulsa una tecla");
	c = my_getc();

	printf("\nTecla pulsada: ");
	my_putc(c);

	printf("\nPulse una tecla para finalizar");
	c = my_getc();

	return 0;
}
