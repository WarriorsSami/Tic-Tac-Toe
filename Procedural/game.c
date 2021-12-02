//
// Created by sami on 02.12.2021.
//

#include "game.h"

game_t* game_init() {
    game_t *game = (game_t*)malloc(sizeof(game_t));

    game->board = (int **)malloc(sizeof(int) * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++) {
        game->board[i] = (int *)malloc(sizeof(int) * BOARD_SIZE);
        for (int j = 0; j < BOARD_SIZE; j++) {
            game->board[i][j] = PLAYER_EMPTY;
        }
    }
    game->current_player = PLAYER_X;
    game->state = GAME_RUNNING;

    return game;
}

void game_free(game_t *game) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        free(game->board[i]);
    }
    free(game->board);
    free(game);
}