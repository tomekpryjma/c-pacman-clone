#pragma once

#include <SDL.h>

typedef struct
{
    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Renderer *renderer;
} GameCore;

void GameCore_Init();