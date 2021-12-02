//
// Created by sami on 02.12.2021.
//

#include "game.h"

game_t* game_init() {
    game_t *game = malloc(sizeof(game_t));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            game->board[i][j] = PLAYER_EMPTY;
        }
    }
    game->current_player = PLAYER_X;
    game->state = GAME_RUNNING;

    return game;
}

void game_free(game_t *game) {
    free(game);
}