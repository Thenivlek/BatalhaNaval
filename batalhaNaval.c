#include <stdio.h>
#include <stdlib.h> // Necessário para usar system("pause")

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define NAVIO 3
#define AGUA 0

// Função para inicializar o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se o navio pode ser posicionado
int podePosicionar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int orientacao) {
    if (orientacao == 0) {
        if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha][coluna + i] != AGUA) return 0;
        }
    } else {
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna] != AGUA) return 0;
        }
    }
    return 1;
}

// Função para posicionar o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (orientacao == 0) {
            tabuleiro[linha][coluna + i] = NAVIO;
        } else {
            tabuleiro[linha + i][coluna] = NAVIO;
        }
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Define posições iniciais dos navios
    int linhaNavioH = 2, colunaNavioH = 3; // navio horizontal
    int linhaNavioV = 5, colunaNavioV = 6; // navio vertical

    // Valida e posiciona navio horizontal
    if (podePosicionar(tabuleiro, linhaNavioH, colunaNavioH, 0)) {
        posicionarNavio(tabuleiro, linhaNavioH, colunaNavioH, 0);
    } else {
        printf("Erro ao posicionar navio horizontal!\n");
        return 1;
    }

    // Valida e posiciona navio vertical
    if (podePosicionar(tabuleiro, linhaNavioV, colunaNavioV, 1)) {
        posicionarNavio(tabuleiro, linhaNavioV, colunaNavioV, 1);
    } else {
        printf("Erro ao posicionar navio vertical!\n");
        return 1;
    }

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    // Pausa para manter o terminal aberto (somente no Windows)
    system("pause");

    return 0;
}
