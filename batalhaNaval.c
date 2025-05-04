#include <stdio.h>
#include <stdlib.h>   // para system("pause")
#include <math.h>     // para abs()

#define TAM_TAB 10
#define TAM_NAVIO 3
#define TAM_HAB 5

// 1) Inicializa todo o tabuleiro com 0 (água)
void inicializarTabuleiro(int tab[TAM_TAB][TAM_TAB]) {
    for (int i = 0; i < TAM_TAB; i++)
        for (int j = 0; j < TAM_TAB; j++)
            tab[i][j] = 0;
}

// 2) Exibe o tabuleiro (0 = ~, 3 = N, 5 = *)
void exibirTabuleiro(int tab[TAM_TAB][TAM_TAB]) {
    for (int i = 0; i < TAM_TAB; i++) {
        for (int j = 0; j < TAM_TAB; j++) {
            if (tab[i][j] == 0)      printf("~ ");
            else if (tab[i][j] == 3) printf("N ");
            else if (tab[i][j] == 5) printf("* ");
        }
        printf("\n");
    }
}

// 3) Verifica se cabe o navio de comprimento TAM_NAVIO na direção (di, dj)
int podePosicionar(int tab[TAM_TAB][TAM_TAB], int linha, int col, int di, int dj) {
    for (int k = 0; k < TAM_NAVIO; k++) {
        int i = linha + k * di;
        int j = col   + k * dj;
        if (i < 0 || i >= TAM_TAB || j < 0 || j >= TAM_TAB || tab[i][j] != 0)
            return 0;
    }
    return 1;
}

// 4) Posiciona o navio
void posicionarNavio(int tab[TAM_TAB][TAM_TAB], int linha, int col, int di, int dj) {
    for (int k = 0; k < TAM_NAVIO; k++) {
        tab[linha + k * di][col + k * dj] = 3;
    }
}

// 5) Gera as matrizes de habilidade (cone, cruz e octaedro)
void gerarCone(int m[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++)
        for (int j = 0; j < TAM_HAB; j++)
            m[i][j] = (j >= TAM_HAB/2 - i && j <= TAM_HAB/2 + i) ? 1 : 0;
}

void gerarCruz(int m[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++)
        for (int j = 0; j < TAM_HAB; j++)
            m[i][j] = (i == TAM_HAB/2 || j == TAM_HAB/2) ? 1 : 0;
}

void gerarOctaedro(int m[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++)
        for (int j = 0; j < TAM_HAB; j++)
            m[i][j] = (abs(i - TAM_HAB/2) + abs(j - TAM_HAB/2) <= TAM_HAB/2) ? 1 : 0;
}
void aplicarCone(int tab[TAM_TAB][TAM_TAB], int cone[TAM_HAB][TAM_HAB], int origem_i, int origem_j) {
    int off = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int ti = origem_i + i;           // <— desloca pra baixo, não sobe
            int tj = origem_j - off + j;     // <— mantém coluna centralizada
            if (ti >= 0 && ti < TAM_TAB && tj >= 0 && tj < TAM_TAB) {
                if (cone[i][j] == 1 && tab[ti][tj] == 0)
                    tab[ti][tj] = 5;
            }
        }
    }
}

// 6) Sobrepõe a habilidade no tabuleiro sem sobrescrever navio (3)
void aplicarHabilidade(int tab[TAM_TAB][TAM_TAB], int hab[TAM_HAB][TAM_HAB], int ori_i, int ori_j) {
    int off = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int ti = ori_i - off + i;
            int tj = ori_j - off + j;
            if (ti >= 0 && ti < TAM_TAB && tj >= 0 && tj < TAM_TAB) {
                if (hab[i][j] && tab[ti][tj] == 0)
                    tab[ti][tj] = 5;
            }
        }
    }
}

int main() {
    int tabuleiro[TAM_TAB][TAM_TAB];
    int cone[TAM_HAB][TAM_HAB], cruz[TAM_HAB][TAM_HAB], octa[TAM_HAB][TAM_HAB];
    inicializarTabuleiro(tabuleiro);

    // --- nível novato+aventureiro: 4 navios de tamanho 3 ---
    // 1 horizontal em (0,1)
    if (podePosicionar(tabuleiro, 0, 1, 0, 1))
        posicionarNavio(tabuleiro, 0, 1, 0, 1);
    // 1 vertical em (2,9)
    if (podePosicionar(tabuleiro, 2, 9, 1, 0))
        posicionarNavio(tabuleiro, 2, 9, 1, 0);
    // 1 diagonal principal "\" em (5,0)
    if (podePosicionar(tabuleiro, 5, 0, 1, 1))
        posicionarNavio(tabuleiro, 5, 0, 1, 1);
    // 1 diagonal secundária "/" em (9,4)
    if (podePosicionar(tabuleiro, 9, 4, -1, 1))
        posicionarNavio(tabuleiro, 9, 4, -1, 1);

    // --- gera matrizes de habilidade ---
    gerarCone(cone);
    gerarCruz(cruz);
    gerarOctaedro(octa);

    // --- aplica habilidades nos pontos de origem definidos ---
    aplicarCone(tabuleiro, cone, 2, 2);

    aplicarHabilidade(tabuleiro, cruz,   5, 5);
    aplicarHabilidade(tabuleiro, octa,   7, 7);

    printf("=== Tabuleiro Nivel Mestre ===\n");
    exibirTabuleiro(tabuleiro);

    system("pause");  // pausa no Windows
    return 0;
}
