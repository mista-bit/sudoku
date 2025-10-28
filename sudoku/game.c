#include <stdio.h>      // I/O
#include <stdlib.h>     // rand, srand, malloc, free
#include <time.h>       // time, clock
#include <locale.h>     // setlocale

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #define Sleep(x) usleep((x)*1000)  // compat: Sleep(ms) em sistemas Unix
#endif

#define N 9
#define VIDAS_INICIAIS 3

typedef struct {
    int tabuleiro[N][N];
    int solucao[N][N];
    int vidas;
} Sudoku;

// valida se num pode ser inserido em (linha,coluna)
int pode_colocar(int grid[N][N], int linha, int coluna, int num) {
    for (int x = 0; x < N; x++)
        if (grid[linha][x] == num || grid[x][coluna] == num)
            return 0;

    int startLinha = linha - linha % 3;
    int startColuna = coluna - coluna % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[startLinha + i][startColuna + j] == num)
                return 0;

    return 1;
}

// backtracking recursivo para resolver o sudoku
int resolver(int grid[N][N]) {
    for (int linha = 0; linha < N; linha++) {
        for (int coluna = 0; coluna < N; coluna++) {
            if (grid[linha][coluna] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (pode_colocar(grid, linha, coluna, num)) {
                        grid[linha][coluna] = num;
                        if (resolver(grid))
                            return 1;
                        grid[linha][coluna] = 0; // backtrack
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

// embaralha vetor de 1–9
void embaralhar(int *nums) {
    for (int i = 0; i < 9; i++) {
        int j = rand() % 9;
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
}

// gera sudoku completo via backtracking + números randomizados
int gerar_completo(int grid[N][N]) {
    int nums[9] = {1,2,3,4,5,6,7,8,9};

    for (int linha = 0; linha < N; linha++) {
        for (int coluna = 0; coluna < N; coluna++) {
            if (grid[linha][coluna] == 0) {
                embaralhar(nums);
                for (int i = 0; i < 9; i++) {
                    int num = nums[i];
                    if (pode_colocar(grid, linha, coluna, num)) {
                        grid[linha][coluna] = num;
                        if (gerar_completo(grid))
                            return 1;
                        grid[linha][coluna] = 0;
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

// remove 'holes' valores aleatórios do grid
void criar_desafio(int grid[N][N], int holes) {
    while (holes > 0) {
        int linha = rand() % N;
        int coluna = rand() % N;
        if (grid[linha][coluna] != 0) {
            grid[linha][coluna] = 0;
            holes--;
        }
    }
}

// copia um grid em outro
void copiar_grid(int origem[N][N], int destino[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            destino[i][j] = origem[i][j];
}

// imprime grid formatado
void mostrar(int grid[N][N]) {
    printf("    1 2 3   4 5 6   7 8 9\n");
    printf("  +-------+-------+-------+\n");

    for (int i = 0; i < N; i++) {
        printf("%d | ", i+1);
        for (int j = 0; j < N; j++) {
            printf(grid[i][j] == 0 ? ". " : "%d ", grid[i][j]);
            if ((j+1)%3 == 0) printf("| ");
        }
        printf("\n");
        if ((i+1)%3 == 0) printf("  +-------+-------+-------+\n");
    }
}

// compara tabuleiro atual com solução
int verificar_vitoria(Sudoku *s) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (s->tabuleiro[i][j] != s->solucao[i][j])
                return 0;
    return 1;
}

// imprime menu de comandos
void mostrar_menu() {
    printf("\n========================================\n");
    printf("COMANDOS:\n");
    printf("  linha coluna número - jogar\n");
    printf("  0 0 0 - sair\n");
    printf("  0 0 1 - ver solução\n");
    printf("  0 0 9 - menu\n");
    printf("========================================\n");
}

// loop principal de jogo
void jogar(Sudoku *s) {
    mostrar_menu();
    while (s->vidas > 0) {
        int linha, coluna, num;
        printf("\nVidas: %d\n", s->vidas);
        scanf("%d %d %d", &linha, &coluna, &num);

        if (linha == 0 && coluna == 0 && num == 0) {
            printf("Saindo...\n");
            break;
        }
        if (linha == 0 && coluna == 0 && num == 1) {
            printf("\nSolução:\n");
            mostrar(s->solucao);
            break;
        }
        if (linha == 0 && coluna == 0 && num == 9) {
            mostrar_menu();
            continue;
        }

        linha--; coluna--;
        if (linha < 0 || linha >= 9 || coluna < 0 || coluna >= 9 || num < 1 || num > 9) {
            printf("Entrada inválida.\n");
            continue;
        }
        if (s->tabuleiro[linha][coluna] != 0) {
            printf("Posição já preenchida.\n");
            continue;
        }

        if (s->solucao[linha][coluna] != num) {
            printf("Número incorreto. -1 vida.\n");
            s->vidas--;
            if (s->vidas == 0) {
                printf("\n*** GAME OVER ***\n");
                printf("Solução:\n");
                mostrar(s->solucao);
                break;
            }
            mostrar(s->tabuleiro);
            continue;
        }

        s->tabuleiro[linha][coluna] = num;
        printf("OK.\n");
        mostrar(s->tabuleiro);

        if (verificar_vitoria(s)) {
            printf("\n+-----------------------------------+\n");
            printf("|  *** PARABÉNS! VOCÊ VENCEU! ***   |\n");
            printf("+-----------------------------------+\n");
            break;
        }
    }
}

// simples animação de loading
void loading_animation(int seconds) {
    const char spinner[] = {'|', '/', '-', '\\'};
    int i = 0;
    clock_t start = clock();

    while (((double)(clock() - start) / CLOCKS_PER_SEC) < seconds) {
        printf("\rGerando Sudoku... %c", spinner[i++ % 4]);
        fflush(stdout);
        Sleep(100);
    }
    printf("\rGerando Sudoku... concluído!\n");
}

int main() {
    #ifdef _WIN32
        SetConsoleOutputCP(65001); // UTF-8 no Windows
    #endif
    setlocale(LC_ALL, "pt_BR.UTF-8");
    srand(time(NULL));

    int easy = 40, normal = 49, hard = 56, impossible = 60;
    int difficulty, difset;

    Sudoku jogo = { .vidas = VIDAS_INICIAIS };

    // inicializa grid
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            jogo.tabuleiro[i][j] = 0;

    loading_animation(1);
    gerar_completo(jogo.tabuleiro);
    copiar_grid(jogo.tabuleiro, jogo.solucao);

    printf("Dificuldade:\n 1 - Fácil\n 2 - Normal\n 3 - Difícil\n 4 - Impossível\n");
    scanf("%d", &difficulty);

    switch(difficulty) {
        case 1: difset = easy; break;
        case 2: difset = normal; break;
        case 3: difset = hard; break;
        case 4: difset = impossible; break;
        default: difset = normal; break;
    }

    criar_desafio(jogo.tabuleiro, difset);

    printf("\nSudoku:\n");
    mostrar(jogo.tabuleiro);
    jogar(&jogo);

    return 0;
}
