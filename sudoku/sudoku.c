#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sudoku.h"

#define N 9

int tabuleiro[N][N];
int tavuleiroOriginal[N][N];

// Função pra verificar se um número pode ser colocado na posição

int pode_numero(int row, int col, int num) {
    // Setor pra verificar a linha
    for (int x = 0; x < N; x++) {
        if (tabuleiro[row][x] == num)
            return 0;
    }

    // Setor pra verificar a coluna
    for (int x = 0; x < N; x++) {
        if (tabuleiro[x][col] == num) {
            return 0;
        }
    }

    // Setor pra verificar o bloco 3x3
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[startRow + i][startCol + j] == num) {
                return 0;
            }
        }
    }

    return 1;
}
 // Função pra encontrar o próximo vazio
int ache_o_vazio(int *row, int *col){
    for (int i = 0; i < N; i++) {
        for (int j = 0 ; j < N; j++) {
            if (tabuleiro[i][j] == 0) {
                *row = i;
                *col = j;
                return 1; 
            }
        }
    }
    return 0;
}

// Backtracking (Ideia de Davi) para preencher o tabuleiro
int resolver_sudoku() {
    int row, col;

    if(!ache_o_vazio(&row, &col)) {
        return 1;
    }

    return 0;
}

