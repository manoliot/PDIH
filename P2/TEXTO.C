#include <stdio.h>
#include "IO.H"

int main()
{
    char c;
    unsigned char mode;

    mode = getvideomode();
    printf("Modo de video: %u", mode);

    printf("\nPulse una tecla: ");
    c = getche();

    printf("\nTecla pulsada: ");
    textbackground(1);
    textcolor(14);
    cputchar(c);

    printf("\nSaltando a la posicion (%i, %i)", 23, 2);
    gotoxy(23, 2);
    c = getche();

    setcursortype(_NOCURSOR);
    printf("\nCambiando a cursor invisible: ");
    c = getch();
    setcursortype(_SOLIDCURSOR);
    printf("\nCambiando a cursor solido: ");
    c = getch();

    printf("\nPulse una tecla para pintar un rectangulo");
    c = getch();
    setcursortype(_NOCURSOR);
    drawrect(20, 5, 60, 20, 2, 5);
    c = getch();

    setcursortype(_NORMALCURSOR);
    textbackground(0);
    textcolor(15);

    printf("\nPulse una tecla para limpiar la pantalla");
    c = getch();
    clrscr();

    printf("\nPulse una tecla finalizar");
    c = getch();
}
