#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BOARD_SIZE 10
#define SHIP_COUNT 5

// Oyun tahtası
char player1board[BOARD_SIZE][BOARD_SIZE];
char player2board[BOARD_SIZE][BOARD_SIZE];

// Gemilerin boyutları
int shipSizes[SHIP_COUNT] = {5, 4, 3, 3, 2};

// Oyun durumu
int gameOver = 0;

// Oyuncu sırası
int currentPlayer = 1;

// Fonksiyon prototipleri
void initializeBoards();
void printBoard(char board[BOARD_SIZE][BOARD_SIZE]);
void placeShips(char board[BOARD_SIZE][BOARD_SIZE]);
void playerTurn(char player1board[BOARD_SIZE][BOARD_SIZE], char player2board[BOARD_SIZE][BOARD_SIZE]);
int checkAttack(int x, int y, char board[BOARD_SIZE][BOARD_SIZE]);
int checkGameOver(char board[BOARD_SIZE][BOARD_SIZE]);
int isPlacementValid(int x, int y, int size, char direction, char board[BOARD_SIZE][BOARD_SIZE]);

int main() {
    initializeBoards();
    
    printBoard(player1board);
    
    printf("Oyuncu 1, gemilerini yerleştirin:\n");
    placeShips(player1board);
    printf("Oyuncu 1 Tahtası (Gemiler Yerleştirildikten Sonra):\n");
    printBoard(player1board);

    printBoard(player2board);
    
    printf("\nOyuncu 2, gemilerini yerleştirin:\n");
    placeShips(player2board);
    printf("Oyuncu 2 Tahtası (Gemiler Yerleştirildikten Sonra):\n");
    printBoard(player2board);

    while (!gameOver) {
        printf("Oyuncu %d Tahtası:\n", currentPlayer);
        if (currentPlayer == 1) {
            playerTurn(player1board, player2board);
        } else {
            playerTurn(player2board, player1board);
        }

        if (checkGameOver(player2board)) {
            printf("Oyun bitti. Oyuncu 1 kazandı!\n");
            break;
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1; // Oyuncu sırasını değiştir

        printf("Oyuncu %d Tahtası:\n", currentPlayer);
        if (currentPlayer == 1) {
            playerTurn(player1board, player2board);
        } else {
            playerTurn(player2board, player1board);
        }

        if (checkGameOver(player1board)) {
            printf("Oyun bitti. Oyuncu 2 kazandı!\n");
            break;
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1; // Oyuncu sırasını değiştir
    }

    return 0;
}

void initializeBoards() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            player1board[i][j] = '~';  // Deniz
            player2board[i][j] = '~'; // Deniz
        }
    }
}

void printBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    printf("  A B C D E F G H I J\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void placeShips(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < SHIP_COUNT; i++) {
        int x, y;
        char direction, yon;

        printf("Gemi %d için başlangıç konumunu ve yönünü girin (örneğin, A3D): ", i + 1);
        scanf(" %c%d%c", &direction, &y, &yon);
        x = toupper(direction) - 'A';

        if (!isPlacementValid(x, y, shipSizes[i], toupper(yon), board)) {
            printf("Geçersiz konum veya yerleştirme. Tekrar deneyin.\n");
            i--;
            continue;
        }

        for (int j = 0; j < shipSizes[i]; j++) {
            if (toupper(yon) == 'D') {
                board[y + j][x] = 'S';
            } else {
                board[y][x + j] = 'S';
            }
        }

        printf("Tahta (Gemiler Yerleştirildikten Sonra):\n");
        printBoard(board);

        // Ek getchar çağrısı
        getchar();
    }
}


void playerTurn(char player1board[BOARD_SIZE][BOARD_SIZE], char player2board[BOARD_SIZE][BOARD_SIZE]) {
    int x, y;
    char column;

    printf("Saldırı yapmak için sütun ve satırı girin (örneğin, B 4): ");
    scanf(" %c %d", &column, &x);
    y = toupper(column) - 'A';

    if (checkAttack(x, y, player2board)) {
        printf("İsabet!\n");
        player1board[x][y] = 'X';
    } else {
        printf("Suya düştü.\n");
        player1board[x][y] = 'O';
    }
}

int checkAttack(int x, int y, char board[BOARD_SIZE][BOARD_SIZE]) {
    if (board[x][y] == 'S') {
        return 1; // İsabet
    } else {
        return 0; // Suya düştü
    }
}

int checkGameOver(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 'S') {
                return 0; // Oyun devam ediyor
            }
        }
    }
    return 1; // Oyun bitti
}

int isPlacementValid(int x, int y, int size, char direction, char board[BOARD_SIZE][BOARD_SIZE]) {
    if (toupper(direction) == 'D') {
        if (y + size > BOARD_SIZE) {
            return 0; // Geçersiz yerleştirme
        }

        for (int i = 0; i < size; i++) {
            if (board[x][y + i] != '~') {
                return 0; // Geçersiz yerleştirme
            }
        }
    } else {
        if (x + size > BOARD_SIZE) {
            return 0; // Geçersiz yerleştirme
        }

        for (int i = 0; i < size; i++) {
            if (board[x + i][y] != '~') {
                return 0; // Geçersiz yerleştirme
            }
        }
    }

    return 1; // Geçerli yerleştirme
}
// bir tane commit atalım bakalım anlaşılcak mı ?