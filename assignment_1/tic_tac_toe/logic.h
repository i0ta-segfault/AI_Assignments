#ifndef LOGIC_H
#define LOGIC_H

#include <stdio.h>

#define BLANK_CELL 2
#define X_CELL 3
#define O_CELL 5
#define MAGIC_SQR_SUM 15

#define ERR_OP -1
#define SUCC_OP 1

extern int board[10];
extern int turn;

void init_board();
int go(int n);
int find_any_blank_cell();
int make2();
int posswin(int player_turn);
void computer_move();
int check_winner();

#endif
