#include <iostream>
#include <SDL2/SDL.h>

#include "Color.hpp"
#include "Object.hpp"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 700

#define PLAYER_SPEED 8.0F

int main(int argc, char* argv[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl unable to init: %s", SDL_GetError());

        return EXIT_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow("Simple SDL2 Collision", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(window == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl unable to create window: %s", SDL_GetError());

        return EXIT_FAILURE;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl unable to create renderer: %s", SDL_GetError());

        return EXIT_FAILURE;
    }

    bool running = true;

    SDL_Event event;
    const Uint8* keys = SDL_GetKeyboardState(nullptr);

    SDL_Color bg = Color::Black();

    Object* player = new Object(50, 50, 0, SCREEN_HEIGHT-50, Color::Red());
    Object* tile = new Object(100, 100, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    keys = SDL_GetKeyboardState(nullptr);
                    break;
            }
        }

        if(keys[SDL_SCANCODE_ESCAPE] == 1)
            running = false;

        if(keys[SDL_SCANCODE_RIGHT] == 1)
            player->Position.x += PLAYER_SPEED;

        if(keys[SDL_SCANCODE_LEFT] == 1)
            player->Position.x -= PLAYER_SPEED;

        if(keys[SDL_SCANCODE_UP] == 1)
            player->Position.y -= PLAYER_SPEED;

        if(keys[SDL_SCANCODE_DOWN] == 1)
            player->Position.y += PLAYER_SPEED;

        SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
        SDL_RenderClear(renderer);

        if(Object::OnCollision(player, tile))
        {
            player->Color = Color::Blue();
            tile->Color = Color::Green();
        }
        else
        {
            player->Color = Color::Red();
            tile->Color = Color::Grey();
        }

        tile->DrawRect(renderer);
        player->DrawRect(renderer);

        SDL_RenderPresent(renderer);

        SDL_Delay(1000/60);
    }

    delete player;
    delete tile;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}