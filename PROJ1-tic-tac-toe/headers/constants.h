#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>
// Window Settings
#define WindowWidth 600
#define WindowHeight 600
#define N 3
#define SCALE 0.8
// Constants
enum {HUMAN, COMPUTER};
enum {EMPTY, WALL, PLAYER_X, PLAYER_O};
enum {GOING, DRAW, PLAYER_X_WIN, PLAYER_O_WIN};
const float Cell_Width = WindowWidth / N;
const float Cell_Height = WindowHeight / N;

SDL_Color Grid_Color_going = {.r=255, .g=255, .b=255 }; // white
SDL_Color Grid_Color_O_win = {.r=255, .g=0,   .b=0 }; // red
SDL_Color Grid_Color_X_win = {.r=0,   .g=0,   .b=255 }; // blue
SDL_Color Grid_Color_draw = {.r=100,  .g=100, .b=100 }; // grey

int initial_board[25] = {WALL, WALL,  WALL,  WALL,  WALL,
                         WALL, EMPTY, EMPTY, EMPTY, WALL,
                         WALL, EMPTY, EMPTY, EMPTY, WALL,
                         WALL, EMPTY, EMPTY, EMPTY, WALL,
                         WALL, WALL,  WALL,  WALL,  WALL};
int board[25] = {WALL, WALL,  WALL,  WALL,  WALL,
                 WALL, EMPTY, EMPTY, EMPTY, WALL,
                 WALL, EMPTY, EMPTY, EMPTY, WALL,
                 WALL, EMPTY, EMPTY, EMPTY, WALL,
                 WALL, WALL,  WALL,  WALL,  WALL};

typedef struct
{
    int *board;
    int player;
    int state;
    int mode;
} game_board;

int to_25_list[9] = {6,7,8,11,12,13,16,17,18};

int to25(const int num)
{
    return to_25_list[num];
}

void copy_board(const int* board1, int* board2)
{
    for (int i = 0; i < (N+2)*(N+2); i++)
    {
        board2[i] = board1[i];
    }
}