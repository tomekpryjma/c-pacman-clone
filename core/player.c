#include "player.h"
#include "globals.h"

Player Player_Setup(Vec initial)
{
    Player player = {
        .position = initial,
        .direction = VEC_UP,
        .canMove = true,
        .countdownTillMove = 0,
        .rect = {.x = initial.x * TILE_SIZE, .y = initial.y * TILE_SIZE, .w = TILE_SIZE, .h = TILE_SIZE}};
    return player;
}

void Player_Update(Player *player, const Uint8 *keyStates, float _delta)
{
    if (player->countdownTillMove > 0)
    {
        player->canMove = false;
        player->countdownTillMove -= 500.0 * _delta;
    }
    else
    {
        player->canMove = true;
    }

    if (player->canMove)
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
    }

    // Vec nextPos = {player->position.x + player->direction.x,
    //                player->position.y + player->direction.y};

    // if (map[nextPos.y][nextPos.x] == 1)
    // {
    //     player->isMoving = false;
    // }

    if (player->isMoving)
    {
        player->position.x += player->direction.x;
        player->position.y += player->direction.y;
        player->rect.x = player->position.x * TILE_SIZE;
        player->rect.y = player->position.y * TILE_SIZE;
        player->isMoving = false;
        player->countdownTillMove = PLAYER_MOVE_DEBOUNCE;
    }
}

void Player_Draw(const Player *player, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &player->rect);
}