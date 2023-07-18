#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>

#define LARGURA 20
#define ALTURA 20

int jogoTerminado;
int pontuacao;
int cobraX, cobraY;
int frutaX, frutaY;
int caldaX[100], caldaY[100];
int tamanhoCalda;
enum Direcao { PARADO = 0, ESQUERDA, DIREITA, CIMA, BAIXO };
enum Direcao dir;

void configurarJogo() {
    jogoTerminado = 0;
    pontuacao = 0;
    cobraX = LARGURA / 2;
    cobraY = ALTURA / 2;
    frutaX = rand() % LARGURA;
    frutaY = rand() % ALTURA;
    dir = PARADO;
}

void desenhar() {
    system("cls");
    int i, j;
    for (i = 0; i < LARGURA + 2; i++)
        printf("#");
    printf("\n");

    for (i = 0; i < ALTURA; i++) {
        for (j = 0; j < LARGURA; j++) {
            if (j == 0)
                printf("#");
            if (i == cobraY && j == cobraX) {
                if (dir == ESQUERDA || dir == DIREITA)
                    printf("o");
                else
                    printf("o");
            } else if (i == frutaY && j == frutaX)
                printf("*");
            else {
                int ehCalda = 0;
                int k;
                for (k = 0; k < tamanhoCalda; k++) {
                    if (caldaX[k] == j && caldaY[k] == i) {
                        printf("o");
                        ehCalda = 1;
                    }
                }
                if (!ehCalda)
                    printf(" ");
            }
            if (j == LARGURA - 1)
                printf("#");
        }
        printf("\n");
    }

    for (i = 0; i < LARGURA + 2; i++)
        printf("#");
    printf("\n");
    printf("Pontuação: %d\n", pontuacao);
}

void entrada() {
    if (_kbhit()) {
        switch (_getch()) {
            case 224: // Código especial para teclas de seta
                switch (_getch()) {
                    case 75: // Seta esquerda
                        if (dir != DIREITA)
                            dir = ESQUERDA;
                        break;
                    case 77: // Seta direita
                        if (dir != ESQUERDA)
                            dir = DIREITA;
                        break;
                    case 72: // Seta cima
                        if (dir != BAIXO)
                            dir = CIMA;
                        break;
                    case 80: // Seta baixo
                        if (dir != CIMA)
                            dir = BAIXO;
                        break;
                }
                break;
            case 'x':
                jogoTerminado = 1;
                break;
        }
    }
}

void logica() {
    int prevX = caldaX[0];
    int prevY = caldaY[0];
    int prev2X, prev2Y;
    caldaX[0] = cobraX;
    caldaY[0] = cobraY;
    int i;
    for (i = 1; i < tamanhoCalda; i++) {
        prev2X = caldaX[i];
        prev2Y = caldaY[i];
        caldaX[i] = prevX;
        caldaY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case ESQUERDA:
            cobraX--;
            break;
        case DIREITA:
            cobraX++;
            break;
        case CIMA:
            cobraY--;
            break;
        case BAIXO:
            cobraY++;
            break;
    }

    if (cobraX < 0) cobraX = LARGURA - 1;
    if (cobraX >= LARGURA) cobraX = 0;
    if (cobraY < 0) cobraY = ALTURA - 1;
    if (cobraY >= ALTURA) cobraY = 0;

    for (i = 0; i < tamanhoCalda; i++) {
        if (caldaX[i] == cobraX && caldaY[i] == cobraY)
            jogoTerminado = 1;
    }

    if (cobraX == frutaX && cobraY == frutaY) {
        pontuacao += 10;
        frutaX = rand() % LARGURA;
        frutaY = rand() % ALTURA;
        tamanhoCalda++;
    }
}

int main() {
    setlocale(LC_ALL, ""); // Configura o programa para usar caracteres UTF-8
    configurarJogo();
    while (!jogoTerminado) {
        desenhar();
        entrada();
        logica();
        Sleep(100);  // Pausa por um curto período para controlar a velocidade
    }
    printf("Fim de Jogo!\n");
    return 0;
}
