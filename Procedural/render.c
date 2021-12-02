#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
//
// Created by sami on 02.12.2021.
//

#include <math.h>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "game.h"

const SDL_Color GRID_COLOR = {.r = 255, .g = 255, .b = 255, .a = 255}; // WHITE
const SDL_Color PLAYER_X_COLOR = {.r = 255, .g = 50, .b = 50, .a = 255}; // LIGHT RED
const SDL_Color PLAYER_O_COLOR = {.r = 50, .g = 100, .b = 255, .a = 255}; // LIGHT BLUE
const SDL_Color TIE_COLOR = {.r = 50, .g = 200, .b = 50, .a = 255}; // GREEN
const SDL_Color INVARIANT_COLOR = {.r = 0, .g = 0, .b = 0, .a = 255}; // BLACK

// render the empty grid
void render_grid(SDL_Renderer *renderer, const SDL_Color *color) {
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);

    for (int i = 1; i < BOARD_SIZE; i++) {
        // draw vertical lines
        SDL_RenderDrawLine(renderer,
                           i * CELL_WIDTH, 0,
                           i * CELL_WIDTH, SCREEN_HEIGHT);
        // draw horizontal lines
        SDL_RenderDrawLine(renderer,
                           0,            i * CELL_HEIGHT,
                           SCREEN_WIDTH, i * CELL_HEIGHT);
    }
}

// render the player's X symbol
void render_x(SDL_Renderer *renderer,
              const int row,
              const int column,
              const SDL_Color *color) {

    const double offset = fmin((double)CELL_WIDTH, (double)CELL_HEIGHT) * 0.25;
    const double x_center = (double)column * CELL_WIDTH + (double)CELL_WIDTH * 0.5;
    const double y_center = (double)row * CELL_HEIGHT + (double)CELL_HEIGHT * 0.5;

    thickLineRGBA(renderer,
                  x_center - offset, y_center - offset,
                  x_center + offset, y_center + offset,
                  10,
                  color->r, color->g, color->b, color->a);
    thickLineRGBA(renderer,
                  x_center + offset, y_center - offset,
                  x_center - offset, y_center + offset,
                  10,
                  color->r, color->g, color->b, color->a);
}

// render the player's O symbol
void render_o(SDL_Renderer *renderer,
              const int row,
              const int column,
              const SDL_Color *color) {

    const double offset = fmin((double)CELL_WIDTH, (double)CELL_HEIGHT) * 0.3;
    const double x_center = (double)column * CELL_WIDTH + (double)CELL_WIDTH * 0.5;
    const double y_center = (double)row * CELL_HEIGHT + (double)CELL_HEIGHT * 0.5;

    filledCircleRGBA(renderer,
                     x_center, y_center,
                     offset,
                     color->r, color->g, color->b, color->a);
    filledCircleRGBA(renderer,
                     x_center, y_center,
                     offset * 0.9,
                     INVARIANT_COLOR.r, INVARIANT_COLOR.g, INVARIANT_COLOR.b, INVARIANT_COLOR.a);
}

// render the game board with the current state (including players' colors)
void render_board(SDL_Renderer *renderer,
                  const int **board,
                  const SDL_Color *player_x_color,
                  const SDL_Color *player_o_color) {

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            switch (board[i][j]) {
                case PLAYER_X:
                    render_x(renderer, i, j, player_x_color);
                    break;
                case PLAYER_O:
                    render_o(renderer, i, j, player_o_color);
                    break;
                default: {}
            }
        }
    }
}

void render_running_state(SDL_Renderer *renderer, const game_t *game) {
    render_grid(renderer, &GRID_COLOR);
    render_board(renderer,
                 (const int **)game->board,
                 &PLAYER_X_COLOR,
                 &PLAYER_O_COLOR);
}

void render_game_over_state(SDL_Renderer *renderer,
                            const game_t *game,
                            const SDL_Color* color) {
    render_grid(renderer, color);
    render_board(renderer,
                 (const int **)game->board,
                 color,
                 color);
}

// render the state of the game to the screen
void render_game(SDL_Renderer *renderer, const game_t *game) {

    switch (game->state) {
        case GAME_RUNNING:
            render_running_state(renderer, game);
            break;
        case GAME_X_WIN:
            render_game_over_state(renderer, game, &PLAYER_X_COLOR);
            break;
        case GAME_O_WIN:
            render_game_over_state(renderer, game, &PLAYER_O_COLOR);
            break;
        case GAME_TIE:
            render_game_over_state(renderer, game, &TIE_COLOR);
            break;
        default: {}
    }
}
#pragma clang diagnostic pop