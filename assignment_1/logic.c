#include "logic.h"

int board[10];
int turn;

int magic_arrangement[9] = {8, 3, 4, 1, 5, 9, 6, 7, 2};

void init_board() {
    for (int i = 1; i < 10; i++) board[i] =  BLANK_CELL;
    turn = 1;
}

int go(int n) {
    if (n < 1 || n > 9 || board[n] != 2) return ERR_OP;
    board[n] = (turn % 2 == 1) ? X_CELL : O_CELL;
    turn += 1;
    return SUCC_OP;
}

int find_any_blank_cell() {
    for (int i = 1; i <= 9; i++) if (board[i] == BLANK_CELL) return i;
    return 0;   // found no blank cell
}

int make2() {
    if (board[5] == BLANK_CELL) return 5;
    for (int i = 1; i <= 9; i++) if (board[i] == BLANK_CELL && (i != 8 && i != 4 && i != 6 && i != 2)) return i;
    return 0;   // no non corner empty cell found
}

int posswin(int player_turn) {  // player_turn indicates X or O
    // compute sum for each pair of sqrs
    // define valid pairs, like what qualifies as a pair
    /*
        8 3 4
        1 5 9
        6 7 2
    */
    int pairs[8][3] = {
        {8, 3, 4},
        {1, 5, 9},
        {6, 7, 2},
        {8, 1, 6},
        {3, 5, 7},
        {4, 9, 2},
        {8, 5, 2},
        {4, 5, 6}
    };
    int magic_positions[10] = {0};  // so the board can't be mapped to magic sqr positions, it'll destory the rendering and bring up wong values, so we make a mapping
    for (int i = 0; i < 9; i++) {
        magic_positions[magic_arrangement[i]] = i + 1;
    }
    int player = player_turn % 2 == 1 ? X_CELL : O_CELL;    // check who the player is, and who the ops are
    for (int i = 0; i < 8; i++) {
        int found_win = 0;
        int player_mark = 0;
        for (int j = 0; j < 3; j++) {
            int pos = magic_positions[pairs[i][j]];
            if (board[pos] == player) player_mark += 1;
            else if (board[pos] == BLANK_CELL) found_win = pos;
        }
        if (player_mark == 2 && found_win) return found_win;
    }
    return 0;   // found no winning move, return 0 next call to this func sld be to block ops move
}

void computer_move() {
    int move_pos = 0;
    switch (turn) {
        case 1 : {
            go(1);
            break;
        }
        case 2 : {
            go(board[5] == BLANK_CELL ? 5 : 1);
            break;
        }
        case 3 : {
            go(board[9] == BLANK_CELL ? 9 : 3);
            break;
        }
        case 4 : {
            move_pos = posswin(X_CELL);
            if (move_pos) go(move_pos);
            else go(make2());
            break;
        }
        case 5 : {
            move_pos = posswin(X_CELL);
            if (move_pos) go(move_pos);
            else if (board[7] == BLANK_CELL) go(7);
            else go(3);
            break;
        }
        case 6 : {
            move_pos = posswin(O_CELL);
            if (move_pos) go(move_pos);
            else if ((move_pos = posswin(X_CELL))) go(move_pos);
            else go(make2());
            break;
        }
        case 7 : {
            move_pos = posswin(X_CELL);
            if (move_pos) go(move_pos);
            else if ((move_pos = posswin(O_CELL))) go(move_pos);
            else go(find_any_blank_cell());
            break;
        }
        case 8 : {
            move_pos = posswin(O_CELL);
            if (move_pos) go(move_pos);
            else if ((move_pos = posswin(X_CELL))) go(move_pos);
            else go(find_any_blank_cell());
            break;
        }
        case 9 : {
            move_pos = posswin(X_CELL);
            if (move_pos) go(move_pos);
            else if ((move_pos = posswin(O_CELL))) go(move_pos);
            else go(find_any_blank_cell());
            break;
        }
    }
}

int check_winner() {
    int lines[8][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9},
        {1, 5, 9},
        {3, 5, 7}
    };
    for (int i = 0; i < 8; i++) {
        int a = lines[i][0], b = lines[i][1], c = lines[i][2];
        if (board[a] == board[b] && board[b] == board[c] && board[a] != BLANK_CELL) {
            return board[a];
        }
    }
    for (int i = 1; i <= 9; i++) {
        if (board[i] == BLANK_CELL) return 0;
    }
    return -1;
}