#include <stdio.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_timer.h"
#include "headers/logic.h"
#include "headers/render.h"
#include "headers/log.h"

int main(int argv, char** args)
{
    // initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Could not initialize: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    // create window
    SDL_Window* MainWindow = SDL_CreateWindow("tic-tac-toe (Press R restart; Press 1 AI Mode; Press 2 Human Mode (default))",
                                            SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED,
                                            WindowWidth,
                                            WindowHeight,
                                            0);
    if (MainWindow == NULL)
    {
        printf("Could not create window: %s\n", SDL_GetError());
        SDL_DestroyWindow(MainWindow);
        SDL_Quit();
        return 0;
    }

    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* renderer = SDL_CreateRenderer(MainWindow, -1, render_flags);    
    if (renderer == NULL)
    {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(MainWindow);
        SDL_Quit();
        return 0;
    }
    // initial the game board
    game_board game_info;
    game_info.board = &board[0];
    game_info.player = PLAYER_X;
    game_info.state = GOING;
    game_info.mode = HUMAN;
    // initial the texture of the pictures
    SDL_Texture* Player_X_texture = init_texture_fromSurface(renderer, "src/playerX.png");
    SDL_Texture* Player_O_texture = init_texture_fromSurface(renderer, "src/playerO.png");

    // main loop
    int CloseSwitch = 0;
    while (!CloseSwitch)
    {
        // input handling
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // quit control
            switch (event.type)
            {
            case SDL_QUIT:
                CloseSwitch = 1;
                break;
            // keyboard control
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_R:
                    refresh_game_board(&game_info);
                    break;
                case SDL_SCANCODE_1:
                    game_info.mode = COMPUTER;
                    break;
                case SDL_SCANCODE_2:
                    game_info.mode = HUMAN;
                default: {}
                }
                break;
            // mouse controll
            case SDL_MOUSEBUTTONDOWN:
                // human move
                click_cell(&game_info, event.button.x / Cell_Width, event.button.y / Cell_Height);
                // AI move
                if (game_info.mode == COMPUTER)
                {
                    check_game_over(&game_info);
                    if (game_info.state == GOING)
                        AIMove(&game_info);
                        check_game_over(&game_info);
                }
                else
                {
                    check_game_over(&game_info);
                }
                //print_board_info(&game_info);
                break;
            default: {}
            }
        }
        // background render
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        // render the gird & board
        render_board(renderer, &game_info, Player_X_texture, Player_O_texture);

        // double buffering
        SDL_RenderPresent(renderer);
    }
    // clean the RAM
    SDL_DestroyTexture(Player_X_texture);
    SDL_DestroyTexture(Player_O_texture);
    SDL_DestroyWindow(MainWindow);
    IMG_Quit();
    SDL_Quit();
    return 0;
}