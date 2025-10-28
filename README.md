# 🧩 Sudoku em C – Geração Aleatória e Backtracking

Projeto desenvolvido para a disciplina **Técnica e Desenvolvimento de Algoritmo**.
A proposta foi criar um **Sudoku jogável no terminal**, que **gera o tabuleiro automaticamente via backtracking recursivo**, com **níveis de dificuldade**, **vidas limitadas** e **interface interativa**.

---

## Sobre o projeto

O programa constrói um **Sudoku completo e válido** utilizando **recursão e tentativa sistemática (backtracking)**, embaralhando números para gerar jogos diferentes a cada execução.
Depois, remove posições aleatoriamente para formar o desafio que o jogador deve resolver.

O jogador escolhe a dificuldade, tem **vidas limitadas** e pode **ver a solução ou sair a qualquer momento**.

Esse projeto foi pensado para exercitar:

* **Recursividade** aplicada a problemas de busca e geração
* **Controle de fluxo** e **manipulação de matrizes**
* **Uso de structs** para organizar o estado do jogo
* **Compatibilidade multiplataforma (Windows e Linux)**
* **Interatividade em linha de comando**

---

## ⚙️ O que o código faz

* Gera um **tabuleiro completo** de Sudoku (9x9)
* Remove células para criar o **desafio** conforme a dificuldade escolhida
* **Valida jogadas** (linha, coluna e bloco 3x3)
* **Controla vidas** do jogador (3 por padrão)
* **Mostra o menu de ajuda e solução** sob comando
* Inclui uma **animação de carregamento** e **menu de dificuldade**

---

## 📂 Estrutura principal

| Função                | Papel                                                       |
| --------------------- | ----------------------------------------------------------- |
| `pode_colocar()`      | Verifica se um número pode ser inserido na posição dada     |
| `resolver()`          | Resolve o Sudoku por backtracking recursivo                 |
| `embaralhar()`        | Embaralha os números de 1–9 para gerar combinações variadas |
| `gerar_completo()`    | Gera um Sudoku completo embaralhando números e recursando   |
| `criar_desafio()`     | Remove células aleatórias para formar o puzzle jogável      |
| `copiar_grid()`       | Copia o tabuleiro original para a solução                   |
| `mostrar()`           | Exibe o tabuleiro formatado no terminal                     |
| `verificar_vitoria()` | Compara o tabuleiro do jogador com a solução                |
| `mostrar_menu()`      | Mostra todos os comandos disponíveis                        |
| `jogar()`             | Controla a lógica principal do jogo e o sistema de vidas    |
| `loading_animation()` | Exibe um pequeno “loading” ao gerar o Sudoku                |

---

## Como rodar

### Compilar

```bash
gcc sudoku.c -o sudoku
```

### Executar

```bash
./sudoku
```

No Windows:

```bash
sudoku.exe
```

---

## Durante o jogo

* `linha coluna número` → faz uma jogada (ex: `3 5 8`)
* `0 0 0` → sair
* `0 0 1` → mostrar a solução e encerrar
* `0 0 9` → mostrar o menu de comandos

---

## Dificuldades disponíveis

| Nível          | Células removidas | Descrição                       |
| -------------- | ----------------- | ------------------------------- |
| 1 – Fácil      | 40                | Desafio leve e acessível        |
| 2 – Normal     | 49                | Equilíbrio entre lógica e sorte |
| 3 – Difícil    | 56                | Exige mais dedução e foco       |
| 4 – Impossível | 60                | Desafio extremo e quase cego    |

---

## Exemplo de saída

```
Gerando Sudoku... concluído!
Dificuldade:
 1 - Fácil
 2 - Normal
 3 - Difícil
 4 - Impossível
2

Sudoku:
    1 2 3   4 5 6   7 8 9
  +-------+-------+-------+
1 | . . . | 7 9 . | . . 2 | 
2 | . 3 . | 4 . . | . 5 . | 
3 | 8 . 5 | . . . | . . . | 
  +-------+-------+-------+
4 | . . . | . . 3 | 9 . . | 
5 | . 4 . | . 8 . | . 7 . | 
6 | . . 2 | . . . | . . . | 
  +-------+-------+-------+
7 | 9 . . | . . . | 3 . 7 | 
8 | . 2 . | 6 . . | . 4 . | 
9 | . . 7 | . . 5 | . . . | 
  +-------+-------+-------+

Vidas: 3
Digite linha(1-9), coluna(1-9), número(1-9)
```

---

## 🧠 Conceitos aplicados

* **Backtracking recursivo** – tanto na geração quanto na solução do Sudoku
* **Controle de estado** usando `struct`
* **Matrizes bidimensionais** (9x9)
* **Aleatoriedade com `rand()` e `srand()`**
* **Compatibilidade multiplataforma** (Windows/Linux)
* **Entrada e saída interativa via `stdio`**
* **Divisão clara de responsabilidades** entre funções
