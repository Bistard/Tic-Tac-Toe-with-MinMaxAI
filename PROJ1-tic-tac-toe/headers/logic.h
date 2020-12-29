#pragma once
#include <SDL2/SDL.h>
#include "constants.h"

void switch_player(game_board* game_info)
{
    if (game_info->player == PLAYER_O) game_info->player = PLAYER_X;
    else game_info->player = PLAYER_O;
}

void click_cell(game_board* game_info, const int j, const int i)
{
    //SDL_Log("click coordinate: (%d,%d) \n \
              player turn: %d \n", i, j, game_info->player);
    
    // place the cell & switch the player
    if ((game_info->board[(to25(i*N+j))] == EMPTY) && (game_info->state == GOING))
    {
        game_info->board[to25(i*N+j)] = game_info->player;
        switch_player(game_info);
    }
}

// return how many cells in a row in the specific direction.
int cells_in_dir(const game_board* game_info, const int position, const int player, const int dir)
{
    if (game_info->board[position] == WALL) return 0;
    else
    {
        if (game_info->board[position] == player) return 1 + cells_in_dir(game_info, position+dir, player, dir);
        else return 0;
    }
}

// 
int findThreeInArow(const game_board* game_info, const int position, const int player, const int dir)
{
    int result;
    result = (cells_in_dir(game_info, to25(position)+dir, player, dir) + 
              cells_in_dir(game_info, to25(position)-dir, player, -dir) + 1);
    return result;
}

// 
void check_game_over(game_board* game_info)
{
    int directions[4] = {1,4,5,6};
    int empty_cells = 0;
    for (int i = 0; i < N*N; i++)
    {
        if (game_info->board[to25(i)] != EMPTY)
        {
            for (int j = 0; j < 4; j++)
            {
                if (findThreeInArow(game_info, i, game_info->board[to25(i)], directions[j]) == 3)
                {
                    if (game_info->board[to25(i)] == PLAYER_O) game_info->state = PLAYER_O_WIN;
                    else game_info->state = PLAYER_X_WIN;
                }
            }
        }
        else empty_cells++;
    }
    if ((empty_cells == 0) && (game_info->state == GOING)) game_info->state = DRAW;
}

void refresh_game_board(game_board* game_info)
{
    for (int i = 0; i < (N+2)*(N+2); i++)
    {
        game_info->board[i] = initial_board[i];
    }
    game_info->state = GOING;
    game_info->player = PLAYER_X;
}

// for the test purpose
void random_comp_move(game_board* game_info)
{
    for (int i = 0; i < N*N; i++)
    {
        if (game_info->board[to25(i)] == EMPTY)
        {
            game_info->board[to25(i)] = game_info->player;
            switch_player(game_info);
            break;
        }
    }
}

// 
int evalScore(game_board* game_info)
{
    check_game_over(game_info);
    if (game_info->player == game_info->state) 
    {
        game_info->state = GOING;
        return 1;
    }
    else if ((game_info->state == DRAW) || (game_info->state == GOING))
    {
        game_info->state = GOING;
        return 0;
    }
    else
    {
        game_info->state = GOING;
        return -1;
    }
}

// return the best move/score for the player
int minMax(game_board* game_info, const int depth)
{
    // base case
    int result = evalScore(game_info);
    if (result != 0)
        return result;

    int avaliableMoves[9];
    int numMoves = 0;
    // find all possible moves
    for (int i = 0; i<N*N; i++)
    {
        if (game_info->board[to25(i)] == EMPTY) 
            avaliableMoves[numMoves++] = i;
    }


    if (numMoves == 0)
        return 0;

    int bestScore = -2;
    int bestMove;
    int score;
    int move;
    // loop all possible moves
    for (int i = 0; i < numMoves; i++)
    {
        move = avaliableMoves[i];
        game_info->board[to25(move)] = game_info->player;
        switch_player(game_info);
        
        score = -minMax(game_info, depth+1);
        
        game_info->board[to25(move)] = EMPTY;
        switch_player(game_info);
        
        if (score > bestScore)
        {
            bestScore = score;
            bestMove = move;
        }
    }

    if (depth != 0)
        return bestScore;
    else
        return bestMove;

}

void AIMove(game_board* game_info)
{
    int bestMove = minMax(game_info, 0);
    game_info->board[to25(bestMove)] = game_info->player;
    switch_player(game_info);
}