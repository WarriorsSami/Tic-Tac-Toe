//
// Created by sami on 02.12.2021.
//

#ifndef PROCEDURAL_GAME_H
#define PROCEDURAL_GAME_H

#define WINDOW_X_POS 100
#define WINDOW_Y_POS 100

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define N 3

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
    int board[N][N];
    int player;
    int state;
} game_t;

void render_game(SDL_Renderer *renderer, const game_t *game);

void update_game(game_t *game, int row, int column);

#endif //PROCEDURAL_GAME_H
