#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TAM 10
#define TAM_NAVIO 3

void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = 0;
}

void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

bool podePosicionar(int tabuleiro[TAM][TAM], int linha, int coluna, int dLinha, int dColuna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha + i * dLinha;
        int c = coluna + i * dColuna;
        if (l < 0 || l >= TAM || c < 0 || c >= TAM || tabuleiro[l][c] != 0)
            return false;
    }
    return true;
}

void posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, int dLinha, int dColuna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha + i * dLinha;
        int c = coluna + i * dColuna;
        tabuleiro[l][c] = 3;
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // Navio em diagonal principal (\) - começa em (0,0), direção (1,1)
    if (podePosicionar(tabuleiro, 0, 0, 1, 1))
        posicionarNavio(tabuleiro, 0, 0, 1, 1);

    // Navio em diagonal secundária (/) - começa em (2,7), direção (1,-1)
    if (podePosicionar(tabuleiro, 2, 7, 1, -1))
        posicionarNavio(tabuleiro, 2, 7, 1, -1);

    printf("\n=== Tabuleiro Aventureiro ===\n");
    exibirTabuleiro(tabuleiro);
    system("pause");

    return 0;
}
