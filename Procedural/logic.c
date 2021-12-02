//
// Created by sami on 02.12.2021.
//

#include "game.h"

void switch_player(game_t *game) {
    if (game->current_player == PLAYER_X) {
        game->current_player = PLAYER_O;
    } else {
        game->current_player = PLAYER_X;
    }
}

// check which player has won
int check_player_win(game_t *game, const Player_State player) {
    // check rows and cols
    int row_count = 0, col_count = 0, first_diag_count = 0, second_diag_count = 0;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (game->board[i][j] == player)
                row_count++;
            if (game->board[j][i] == player)
                col_count++;
        }
        // check if row or col has enough cells for declaring a win
        if (row_count >= BOARD_SIZE || col_count >= BOARD_SIZE)
            return 1;

        // reset counters otherwise
        row_count = col_count = 0;

        // check diagonals
        if (game->board[i][i] == player)
            first_diag_count++;
        if (game->board[i][BOARD_SIZE - i - 1] == player)
            second_diag_count++;
    }
    return first_diag_count >= BOARD_SIZE || second_diag_count >= BOARD_SIZE;
}

int count_cells(game_t *game, const Player_State cell_type) {
    int count = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (game->board[i][j] == cell_type) {
                count++;
            }
        }
    }
    return count;
}

// handle game over situation
void check_game_over(game_t *game) {
    if (check_player_win(game, PLAYER_X)) {
        game->state = GAME_X_WIN;
    } else if (check_player_win(game, PLAYER_O)) {
        game->state = GAME_O_WIN;
    } else if (count_cells(game, PLAYER_EMPTY) == 0) {
        game->state = GAME_TIE;
    }
}

// handle current player's turn
void player_turn(game_t *game, const int row, const int column) {
    if (game->board[row][column] == PLAYER_EMPTY) {
        game->board[row][column] = game->current_player;
        switch_player(game);
        check_game_over(game);
    }
}

// reset the state of the game
void reset_game(game_t *game) {
   game->current_player = PLAYER_X;
   game->state = GAME_RUNNING;
   for (int i = 0; i < BOARD_SIZE; i++) {
       for (int j = 0; j < BOARD_SIZE; j++) {
           game->board[i][j] = PLAYER_EMPTY;
       }
   }
}

// update the state of the game when a certain cell is selected
void update_game(game_t *game, const int row, const int column) {
    if (game->state == GAME_RUNNING) {
        player_turn(game, row, column);
    } else {
        reset_game(game);
    }
}
