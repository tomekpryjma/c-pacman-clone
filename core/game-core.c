#include "game-core.h"
#include <stdio.h>

void GameCore_Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("%s\n", SDL_GetError());
        exit(1);
    }
}