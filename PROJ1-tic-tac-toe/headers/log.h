#pragma once
#include <SDL2/SDL.h>
#include "constants.h"

const char* game_state_list[4] = {"GOING","DRAW","PLAYER_X_WIN","PLAYER_O_WIN"};


void print_board_info(const game_board* game_info)
{
    SDL_Log("game state: %s", game_state_list[game_info->state]);
    SDL_Log("game board:");
    SDL_Log("%d %d %d", game_info->board[6],game_info->board[7],game_info->board[8]);
    SDL_Log("%d %d %d", game_info->board[11],game_info->board[12],game_info->board[13]);
    SDL_Log("%d %d %d", game_info->board[16],game_info->board[17],game_info->board[18]);
}
