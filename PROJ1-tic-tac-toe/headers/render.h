#pragma once
#include <stdio.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "constants.h"

void render_grid(SDL_Renderer *renderer, const game_board *game, const SDL_Color *color)
{
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);
    for (int i = 0; i < N; i++)
    {
        // horizontal lines
        SDL_RenderDrawLine(renderer,
                           0,i*Cell_Width,
                           WindowWidth,i*Cell_Width);
        // vertical lines
        SDL_RenderDrawLine(renderer,
                          i*Cell_Height,0,
                          i*Cell_Height,WindowHeight);
    }
}

SDL_Texture* init_texture_fromSurface(SDL_Renderer* renderer, const char* path)
{
    SDL_Surface* image = IMG_Load(path);
    // error handling
    if (image == NULL)
    {
        printf("IMG_load error: %s\n", SDL_GetError());
        return NULL;
    }
    SDL_Texture* image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return image_texture;
}

void render_player_x(SDL_Renderer *renderer,
                     SDL_Texture *texture,
                     const int y, const int x)
{
    SDL_Rect texture_destination;
    texture_destination.x = x * Cell_Width + ((1-SCALE) * Cell_Width) / 2;
    texture_destination.y = y * Cell_Height + ((1-SCALE) * Cell_Height) / 2;
    texture_destination.w = SCALE * Cell_Width;
    texture_destination.h = SCALE * Cell_Height;
    SDL_RenderCopy(renderer, texture, NULL, &texture_destination);
}

void render_player_o(SDL_Renderer *renderer,
                     SDL_Texture *texture,
                     const int y, const int x)
{
    SDL_Rect texture_destination;
    texture_destination.x = x * Cell_Width + ((1-SCALE) * Cell_Width) / 2;
    texture_destination.y = y * Cell_Height + ((1-SCALE) * Cell_Height) / 2;
    texture_destination.w = SCALE * Cell_Width;
    texture_destination.h = SCALE * Cell_Height;
    SDL_RenderCopy(renderer, texture, NULL, &texture_destination);
}

void render_board(SDL_Renderer *renderer, const game_board *game,
                  SDL_Texture *PlayerX_texture,
                  SDL_Texture *PlayerO_texture)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            switch (game->board[to25(i*N + j)])
            {
            case PLAYER_O:
                render_player_o(renderer, PlayerO_texture, i, j);
                break;
            case PLAYER_X:
                render_player_x(renderer, PlayerX_texture, i, j);
                break;
            default: {}
            }
        }
    }
    // render grid
    switch (game->state)
        {
        case GOING:
            render_grid(renderer, game, &Grid_Color_going);
            break;
        case PLAYER_X_WIN:
            render_grid(renderer, game, &Grid_Color_X_win);
            break;
        case PLAYER_O_WIN:
            render_grid(renderer, game, &Grid_Color_O_win);
            break;
        case DRAW:
            render_grid(renderer, game, &Grid_Color_draw);
            break;
        default: {}
        }
}

