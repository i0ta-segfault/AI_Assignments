#include <stdlib.h>
#include "logic.h"

void draw_board() {
    printf("\n");
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            int pos = row * 3 + col + 1;
            if (board[pos] == X_CELL)
                printf(" X ");
            else if (board[pos] == O_CELL)
                printf(" O ");
            else
                printf(" %d ", pos);

            if (col < 2) printf("|");
        }
        printf("\n");
        if (row < 2) printf("---+---+---\n");
    }
    printf("\n");
}

int main() {
    int winner = 0;
    int game_over = 0;

    init_board();
    printf("Tic-Tac-Toe: You are X, Computer is O\n");

    while (!game_over) {
        draw_board();
        if (turn % 2 == 1) {
            int pos;
            printf("Enter your move (1-9): ");
            scanf("%d", &pos);
            if (pos >= 1 && pos <= 9 && board[pos] == BLANK_CELL) {
                board[pos] = X_CELL;
                turn++;
            } else {
                printf("Invalid move. Try again.\n");
                continue;
            }
        } else {
            computer_move();
        }

        winner = check_winner();
        if (winner != 0) game_over = 1;
    }

    draw_board();

    if (winner == X_CELL) printf("You win!\n");
    else if (winner == O_CELL) printf("Computer wins!\n");
    else if (winner == -1) printf("It's a draw!\n");

    return 0;
}
