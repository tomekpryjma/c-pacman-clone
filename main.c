#include <stdio.h>
#include <stdbool.h>
#include "core/game-core.h"
#include "core/globals.h"
#include "core/vectors.h"
#include "core/player.h"

int g_Map[MAP_SIZE][MAP_SIZE] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void Map_Draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int row = 0; row < MAP_SIZE; row++)
    {
        for (int col = 0; col < MAP_SIZE; col++)
        {
            if (g_Map[row][col] == 1)
            {
                SDL_RenderFillRect(renderer, &(SDL_Rect){col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE});
            }
        }
    }
}

int main()
{
    GameCore_Init();

    // === Setup ===

    GameCore gc;

    if (SDL_CreateWindowAndRenderer(WIN_WIDTH, WIN_WIDTH, 0, &gc.window, &gc.renderer) != 0)
    {
        SDL_Log("Error setting up window and/or renderer: %s", SDL_GetError());
        exit(1);
    }

    // === Loop ===

    float _delta = 0.0;
    Uint32 _last = SDL_GetTicks();
    Player player = Player_Setup((Vec){MAP_SIZE / 2, MAP_SIZE / 2});
    SDL_Event e;
    const Uint8 *keyStates;
    bool isRunning = true;

    while (isRunning)
    {
        _delta = (float)(SDL_GetTicks() - _last) / 1000.0;
        _last = SDL_GetTicks();
        if (_delta > 0.016)
        {
            _delta = 0.016;
        }

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }

        keyStates = SDL_GetKeyboardState(NULL);

        Player_Update(&player, keyStates, _delta);

        SDL_SetRenderDrawColor(gc.renderer, 0, 0, 0, 255); // Black
        SDL_RenderClear(gc.renderer);
        Map_Draw(gc.renderer);
        Player_Draw(&player, gc.renderer);

        SDL_RenderPresent(gc.renderer);
    }

    SDL_DestroyRenderer(gc.renderer);
    SDL_DestroyWindow(gc.window);
    SDL_Quit();

    return 0;
}