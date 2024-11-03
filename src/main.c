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
#include <time.h>
#include <unistd.h>


int x = 34, y = 5;
int incX = 1, incY = 1;
int incNave = 1;
int x_nave = 32, y_nave = 17;
int x_pontuacao = 0, y_pontuacao = 0;
int x_time = MAXX - 50, y_time = 32;
time_t startTime;
double velocidade = 50;


int time_decorrido = 0;

/*void printHello(int nextX, int nextY)
{
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(x, y);
    printf("           ");
    x = nextX;
    y = nextY;
    screenGotoxy(x, y);
    printf("Hello World");
}*/


void displayTimer() {
    screenSetColor(CYAN, DARKGRAY);

    time_t currentTime = time(NULL);
    int elapsedTime = (int)(currentTime - startTime);


    int minutes = elapsedTime / 60;
    int seconds = elapsedTime % 60;

    screenGotoxy(x_time, y_time);
    printf("Tempo decorrido: %02d:%02d", minutes, seconds);
    fflush(stdout);
    int time_decorrido = time_decorrido + 1;
}

void pontuacao_total(int vida){

    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(x_pontuacao, y_pontuacao);
    int newVida = vida;
    printf(" Sua vida é: %d ", newVida);


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
    printf("       ");
    x_nave = naveX;
    y_nave = MAXY - 2;
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
    startTime = time(NULL);
    static int ch = 0;

    screenInit(1);
    keyboardInit();
    timerInit(50);

    meteoros(x, y);
    screenUpdate();
    int pontuacao = 100;


    while (pontuacao != 0) //enter
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

            

            if (newY >= MAXY){
                newX = (rand() % (MAXX - 4)) + 3;
                newY = MINY + 3;
            }


            if (ch == 'd' && x_nave < MAXX - 7){
                naveEixo = x_nave + incNave;
            }else if (ch == 'a' && x_nave > MINX + 2){
                naveEixo = x_nave - incNave;
            }

            if (y == y_nave && x >= x_nave && x <= x_nave + 4){
                newX = (rand() % (MAXX - 4)) + 3;
                newY = MINY + 3;
                pontuacao = pontuacao - 10;
            }
                 
            switch (time_decorrido) {
                case 300:  // Após 5 minutos
                    velocidade = 40;
                    timerInit(velocidade);
                    break;
                case 600:  
                    velocidade = 35;
                    timerInit(velocidade);
                    break;
                case 1200:  
                    velocidade = 25;
                    timerInit(velocidade);
                    break;
                default:
                    break;
            }

            time_decorrido++;
            //printf("%d", time_decorrido);
            //x_nave = naveEixo;

            //printf("%d", elapsedTime);
            //printKey(ch);
            time_decorrido = time_decorrido + 1;
            displayTimer();
            meteoros(newX, newY);
            nave(naveEixo);
            pontuacao_total(pontuacao);
            //printHello(newX, newY);

            screenUpdate();
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}



