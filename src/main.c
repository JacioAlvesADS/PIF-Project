/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include <string.h>
#include <stdlib.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int x = 34, y = 5;
int incX = 1, incY = 1;
int incNave = 1;
int x_nave = 32, y_nave = 12;

void printHello(int nextX, int nextY)
{
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(x, y);
    printf("           ");
    x = nextX;
    y = nextY;
    screenGotoxy(x, y);
    printf("Hello World");
}


void meteoros(int nextX, int nextY){
    screenSetColor(RED, DARKGRAY);
    screenGotoxy(x, y);
    printf(" ");
    x = nextX;
    y = nextY;
    screenGotoxy(x, y);
    printf("0");
}

void nave(int naveX){
    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(x_nave, y_nave);
    printf("      ");
    x_nave = naveX;
    y_nave = 16;
    screenGotoxy(x_nave, y_nave);
    printf("=====");

}

void printKey(int ch)
{
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(35, 22);
    printf("Key code :");

    screenGotoxy(34, 23);
    printf("            ");
    
    if (ch == 27) screenGotoxy(36, 23);
    else screenGotoxy(39, 23);

    printf("%d ", ch);
    while (keyhit())
    {
        printf("%d ", readch());
    }
}

int main() 
{
    static int ch = 0;

    screenInit(1);
    keyboardInit();
    timerInit(50);

    meteoros(x, y);
    screenUpdate();

    while (ch != 10) //enter
    {
        // Handle user input
        if (keyhit()) 
        {
            ch = readch();
            //printKey(ch);
            screenUpdate();
        }

        // Update game state (move elements, verify collision, etc)
        if (timerTimeOver() == 1)
        {
            int newX;
            int newY = y + incY;
            int naveEixo = x_nave;

            

            if (newY >= MAXY - 6){
                newX = (rand() % (MAXX - 4)) + 3;
                newY = MINY + 3;
            }


            if (ch == 'd' && x_nave < MAXX - 7){
                naveEixo = x_nave + incNave;
            }else if (ch == 'a' && x_nave > MINX + 2){
                naveEixo = x_nave - incNave;
            }

            if (y == y_nave && x >= x_nave && x <= x_nave + 4){
                break;
            }

            //x_nave = naveEixo;

            //printf("%d",x_nave);
            //printKey(ch);
            meteoros(newX, newY);
            nave(naveEixo);
            //printHello(newX, newY);

            screenUpdate();
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}



