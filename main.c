#include <stdio.h>
#include <stdbool.h>
#include "core/game-core.h"

#define WIN_WIDTH 400
#define WIN_HEIGHT 400
#define MAP_SIZE 12
#define TILE_SIZE 10
#define VEC_UP \
    (Vec) { 0, -1 }
#define VEC_DOWN \
    (Vec) { 0, 1 }
#define VEC_LEFT \
    (Vec) { -1, 0 }
#define VEC_RIGHT \
    (Vec) { 0, 1 }

typedef struct
{
    int x, y;
} Vec;

typedef struct
{
    bool isAlive;
    bool isMoving;
    Vec direction;
    Vec position;
    SDL_Rect rect;
} Player;

Player Player_Setup(Vec initial)
{
    Player player = {
        .position = initial,
        .direction = VEC_UP,
        .rect = {.x = initial.x * TILE_SIZE, .y = initial.y * TILE_SIZE, .w = TILE_SIZE, .h = TILE_SIZE}};
    return player;
}

void Player_Update(Player *player, const Uint8 *keyStates, float _delta)
{
    if (keyStates[SDL_SCANCODE_UP])
    {
        player->isMoving = true;
        player->direction = VEC_UP;
    }
    else if (keyStates[SDL_SCANCODE_DOWN])
    {
        player->isMoving = true;
        player->direction = VEC_DOWN;
    }
    else if (keyStates[SDL_SCANCODE_LEFT])
    {
        player->isMoving = true;
        player->direction = VEC_LEFT;
    }
    else if (keyStates[SDL_SCANCODE_RIGHT])
    {
        player->isMoving = true;
        player->direction = VEC_RIGHT;
    }

    if (player->isMoving)
    {
        player->position.x += player->direction.x;
        player->position.y += player->direction.y;
        player->rect.x = player->position.x * TILE_SIZE;
        player->rect.y = player->position.y * TILE_SIZE;
    }
}

void Player_Draw(const Player *player, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &player->rect);
}

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

    float _delta = 0;
    Uint32 _last = SDL_GetTicks();
    Player player = Player_Setup((Vec){MAP_SIZE / 2, MAP_SIZE / 2});
    SDL_Event e;
    const Uint8 *keyStates;
    bool isRunning = true;

    while (isRunning)
    {
        _delta = (SDL_GetTicks() - _last) / 1000;
        _last = SDL_GetTicks();

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