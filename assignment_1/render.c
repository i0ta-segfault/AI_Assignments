// just so i don't forget - this was the build command
// gcc -o render render.c logic.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
// TODO : write a makefile for this

#include <raylib.h>
#include "logic.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define TILE_SIZE 200

int winner = 0;
int game_over = 0;

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT + 100, "Tic-Tac-Toe | Computer is O");
    SetTargetFPS(60);
    init_board();
    while(!WindowShouldClose()) {
        ClearBackground(BLACK);
        if (!game_over) {
            if ((turn % 2 == 1) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) { // i am assuming player is X and computer is O
                Vector2 mousePos = GetMousePosition();
                int col = mousePos.x / TILE_SIZE;
                int row = mousePos.y / TILE_SIZE;
                int pos = row * 3 + col + 1;
                if (pos >= 1 && pos <= 9 && board[pos] == BLANK_CELL) {
                    board[pos] = X_CELL;
                    turn += 1;
                }
            }
            else if (turn % 2 == 0) computer_move(); 
            winner = check_winner();
            if (winner != 0) game_over = true;
        }
        
        BeginDrawing();
            // verticals
            DrawLine(TILE_SIZE, 0, TILE_SIZE, SCREEN_HEIGHT, PINK);
            DrawLine(TILE_SIZE * 2, 0, TILE_SIZE * 2, SCREEN_HEIGHT, PINK);
            // horizontals
            DrawLine(0, TILE_SIZE, SCREEN_WIDTH, TILE_SIZE, PINK);
            DrawLine(0, TILE_SIZE * 2, SCREEN_WIDTH, TILE_SIZE * 2, PINK);
            for (int i = 1; i <= 9; i++) {
                int row = (i - 1) / 3;
                int col = (i - 1) % 3;
                int x = col * TILE_SIZE;
                int y = row * TILE_SIZE;
                if (board[i] == X_CELL) {
                    DrawLine(x + 30, y + 30, x + TILE_SIZE - 30, y + TILE_SIZE - 30, RED);
                    DrawLine(x + TILE_SIZE - 30, y + 30, x + 30, y + TILE_SIZE - 30, RED);
                }
                else if (board[i] == O_CELL) {
                    DrawCircleLines(x + TILE_SIZE / 2, y + TILE_SIZE / 2, TILE_SIZE / 2 - 30, GREEN);
                }
            }
            DrawLine(0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, RAYWHITE);
            if (game_over) {
                if (winner == X_CELL) DrawText("Player (X) Wins!", 200, 650, 20, RAYWHITE);
                else if (winner == O_CELL) DrawText("Computer (O) Wins!", 200, 650, 20, RAYWHITE);
                else if (winner == -1) DrawText("It's a Draw!", 220, 650, 20, RAYWHITE);
            }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}