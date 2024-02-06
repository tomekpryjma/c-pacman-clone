#pragma once

#include <stdbool.h>
#include <SDL.h>
#include "vectors.h"
#include "globals.h"

typedef struct
{
    bool isAlive;
    bool isMoving;
    bool canMove;
    float countdownTillMove;
    Vec direction;
    Vec position;
    SDL_Rect rect;
} Player;

Player Player_Setup(Vec initial);
void Player_Update(Player *player, const Uint8 *keyStates, float _delta);
void Player_Draw(const Player *player, SDL_Renderer *renderer);