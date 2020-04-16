#include <stdio.h>
#include "IO.H"

#define HEIGHT      200
#define WIDTH       320
#define SNAKE_COLOR 1
#define FOOD_COLOR  3
#define TILE_SIZE   6


int main()
{
    int x, y;
    byte color = 2;

    setvideomode(0x13);

    // Banda superior
    for(y=0; y<10; y++) {
        for(x=0; x<320; x++) {
            drawpx(x, y, (x >> 4) % 16);
        }
    }

    // L
    color = 2;
    for(y=50; y<150; y++) {
        for(x=40; x<60; x++) {
            drawpx(x, y, color);
        }
    }
    for(y=130; y<150; y++) {
        for(x=60; x<100; x++) {
            drawpx(x, y, color);
        }
    }

    // O
    color = 3;
    for(y=50; y<150; y++) {
        if(y<70 || y >=130) {
            for(x=120; x<200; x++) {
                drawpx(x, y, color);
            }
        } else {
            for(x=0; x<20; x++) {
                drawpx(120+x, y, color);
                drawpx(199-x, y, color);
            }
        }
    }

    // L
    color = 4;
    for(y=50; y<150; y++) {
        for(x=220; x<240; x++) {
            drawpx(x, y, color);
        }
    }
    for(y=130; y<150; y++) {
        for(x=240; x<280; x++) {
            drawpx(x, y, color);
        }
    }

    // Banda inferior
    for(y=190; y<200; y++) {
        for(x=0; x<320; x++) {
            drawpx(x, y, 15 - ((x >> 4) % 16));
        }
    }

    getch();
    setvideomode(3);
}
