#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include "./game.h"

const float cell_width = SCREEN_WIDTH / (float) N;
const float cell_height = SCREEN_HEIGHT / (float) N;

int main(int argc, char *argv[]) {
    // initialize SDL video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr,"SDL_Init Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // instantiate a window
    SDL_Window *window = SDL_CreateWindow("Tic-Tac-Toe Procedural",
                                          WINDOW_X_POS, WINDOW_Y_POS,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);

    // check if window was created
    if (window == NULL) {
        fprintf(stderr,"SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // instantiate a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                                SDL_RENDERER_ACCELERATED |
                                                SDL_RENDERER_PRESENTVSYNC);

    // check if renderer was created
    if (renderer == NULL) {
        fprintf(stderr,"SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // instantiate an instance of the game (empty board)
    game_t *game = game_init();

    // check if game was created
    if (game == NULL) {
        fprintf(stderr, "game_init Error\n");
        return EXIT_FAILURE;
    }

    // spawn the event game loop
    SDL_Event event;
    while (game->state != GAME_QUIT) {
        // check for events
        while (SDL_PollEvent(&event)) {
            // check for quit event
            switch(event.type) {
                case SDL_QUIT:
                    game->state = GAME_QUIT;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    update_game(game,
                                event.button.x / (int) cell_width,
                                event.button.y / (int) cell_height);
                    break;
                default: {

                }
            }
        }

        // clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // draw the screen
        render_game(renderer, game);
        SDL_RenderPresent(renderer);
    }

    // deallocate the resources
    SDL_DestroyWindow(window);
    SDL_Quit();
    game_free(game);

    return EXIT_SUCCESS;
}
