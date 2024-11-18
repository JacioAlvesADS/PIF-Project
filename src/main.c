/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include <time.h>
#include <unistd.h>
#define MAX_NOME 100

int x = 34, y = 5;
int x_dificil = 34, y_dificil = 5;
int incX = 1, incY = 1;
int incNave = 1;
int x_nave = 32, y_nave = 17;
int x_pontuacao = 0, y_pontuacao = 0;
int x_time = MAXX - 45, y_time = 32;
time_t startTime;
double velocidade = 50;
char continuar;



int long long time_decorrido = 0;

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

struct Jogador {
    char nome[50];      
    long long pontuacao; 
};

void inserirDados(struct Jogador jogador) {
    sqlite3 *db;
    char *erroMsg = 0;
    int rc;
    char sql[256];

    rc = sqlite3_open("players.db", &db);
    if (rc) {
        fprintf(stderr, "Erro ao abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        return;
    }

    snprintf(sql, sizeof(sql), "INSERT INTO players (nome, pontuacao) VALUES ('%s', %lld);", 
             jogador.nome, jogador.pontuacao);

    rc = sqlite3_exec(db, sql, 0, 0, &erroMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao inserir os dados: %s\n", erroMsg);
        sqlite3_free(erroMsg);
    } else {
        printf("Dados inseridos com sucesso.\n");
    }

    sqlite3_close(db);
}

void displayTimer() {
    screenSetColor(CYAN, DARKGRAY);

    time_t currentTime = time(NULL);
    int elapsedTime = (int)(currentTime - startTime);


    screenGotoxy(x_time, y_time);
    printf("Pontuação: %lld", time_decorrido);
    //int time_decorrido = time_decorrido + 10;
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

void meteoros_dificil(int meteoroX, int meteoroY) {
    int* coords = (int*)malloc(2 * sizeof(int));
    if (coords == NULL) {
        fprintf(stderr, "Erro ao alocar memória para as coordenadas do meteoro.\n");
        return;
    }

    coords[0] = x_dificil;
    coords[1] = y_dificil;

   
    screenSetColor(BLUE, DARKGRAY);
    screenGotoxy(coords[0], coords[1]);
    printf(" ");

    
    coords[0] = meteoroX;
    coords[1] = meteoroY;
    x_dificil = coords[0];
    y_dificil = coords[1];

    screenGotoxy(x_dificil, y_dificil);
    printf("0"); 
    free(coords);
}
void comecar(int x_comecar, int y_comecar){
    screenSetColor(RED, DARKGRAY);
    screenGotoxy(x_comecar, y_comecar);
    //printf("              ");
    screenGotoxy(x_comecar, y_comecar);
    printf("Começar Jogo!\n");
    printf("                              Aperte 's' para começar\n");
}

void nave(int naveX){
    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(x_nave, y_nave);
    printf("       ");
    x_nave = naveX;
    y_nave = MAXY - 2;
    screenGotoxy(x_nave, y_nave);
    printf("8___8");

}


void reiniciarJogo() {
    x = 34, y = 5;
    x_dificil = 34, y_dificil = 5;
    x_nave = 32, y_nave = 17;
    time_decorrido = 0;
    startTime = time(NULL);
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
    char jogarNovamente;

    screenInit(1);
    keyboardInit();
    timerInit(50);
    struct Jogador jogador1;

    meteoros(x, y);
    screenUpdate();
    int pontuacao = 100;
    //char continuar;
    //comecar(32, 15);

    while(continuar != 's'){
        comecar(34,5);
        scanf("%c", &continuar);
    }
    screenGotoxy(34,5);
    printf("                        \n");
    screenGotoxy(30,6);
    printf("                           ");

    while (pontuacao != 0) //enter
    {
        //comecar(1000,1000);
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
            int meteoroPositionX;
            int meteoroPositionY = y_dificil + incY;
            int positionBotton = x + incY;
            int positionBotton_y;
            

            if (newY >= MAXY){
                newX = (rand() % (MAXX - 4)) + 3; //Movimentação do Meteoro
                newY = MINY + 3;
            }


            if (ch == 'd' && x_nave < MAXX - 7){
                naveEixo = x_nave + incNave;//Movimentação da Nave
            }else if (ch == 'a' && x_nave > MINX + 2){
                naveEixo = x_nave - incNave;
            }

            if (y == y_nave && x >= x_nave && x <= x_nave + 4){
                newX = (rand() % (MAXX - 4)) + 3;
                newY = MINY + 3;//Colidir o Meteoro com a nave.
                velocidade = 50;
                pontuacao = pontuacao - 10;
                
            }
            if (time_decorrido >= 600){
                if (meteoroPositionY >= MAXY){
                    meteoroPositionX = (rand() % (MAXX - 4)) + 3; //Movimentação do Meteoro
                    meteoroPositionY = MINY + 3;
                    }
                if (y_dificil == y_nave && x_dificil >= x_nave && x_dificil <= x_nave + 4){
                    meteoroPositionX = (rand() % (MAXX - 4)) + 3;
                    meteoroPositionY = MINY + 3;//Colidir o Meteoro com a nave.
                    pontuacao = pontuacao - 10;
                
            }

            }
                 
            switch (time_decorrido) {
                case 300:  // Variando a velocidade ao longo do tempo
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

            time_decorrido = time_decorrido + 1;
            //printf("%d", time_decorrido);
            //x_nave = naveEixo;

            //printf("%d", elapsedTime);
            //printKey(ch);
            //time_decorrido = time_decorrido + 1;
            displayTimer();
            meteoros(newX, newY);
            nave(naveEixo);
            meteoros_dificil(meteoroPositionX, meteoroPositionY);
            pontuacao_total(pontuacao);
            //printHello(newX, newY);

            screenUpdate();
        }
    }
    while (pontuacao == 0)
    {
        printf("\nDigite seu nome: ");
        int i = 0;
        char ch;

        while (1) {
            ch = getchar(); 
            if (ch == '\n' || i >= MAX_NOME - 1) { 
                break;
            }
            jogador1.nome[i] = ch; 
            i++;
            putchar(ch);
        }

        jogador1.nome[i] = '\0';
        jogador1.pontuacao = time_decorrido;

        // Exibe os dados do jogador
        printf("\n--- Fim do Jogo ---\n");
        printf("Nome: %s\n", jogador1.nome);
        printf("Pontuação: %lld\n", jogador1.pontuacao);

        printf("Deseja jogar novamente?(s/n)");
        scanf("%c", &jogarNovamente);

        if( jogarNovamente == 's' ){
            time_decorrido = 0;
            main();
            pontuacao = 100;

        }else if(jogarNovamente == 'n'){
            inserirDados(jogador1);
            break;
        }


        }
        

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}



