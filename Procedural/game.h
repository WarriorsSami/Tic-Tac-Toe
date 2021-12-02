//
// Created by sami on 02.12.2021.
//

#ifndef PROCEDURAL_GAME_H
#define PROCEDURAL_GAME_H

#include <SDL2/SDL_render.h>

#define WINDOW_X_POS 100
#define WINDOW_Y_POS 100

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

#define BOARD_SIZE 3

#define CELL_WIDTH SCREEN_WIDTH / BOARD_SIZE
#define CELL_HEIGHT SCREEN_HEIGHT / BOARD_SIZE

enum Player_State {
    PLAYER_EMPTY,
    PLAYER_X,
    PLAYER_O
};

enum Game_State {
    GAME_RUNNING,
    GAME_X_WIN,
    GAME_O_WIN,
    GAME_TIE,
    GAME_QUIT
};

typedef struct {
    int **board;
    int current_player;
    int state;
} game_t;

game_t* game_init();

void game_free(game_t *game);

void render_game(SDL_Renderer *renderer, const game_t *game);

void update_game(game_t *game, int row, int column);

#endif //PROCEDURAL_GAME_H
