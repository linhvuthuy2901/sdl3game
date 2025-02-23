#include "SDL3/SDL_video.h"
#include "sdl3/SDL_render.h"
#include <cstddef>
#define SDL_MAIN_USE_CALLBACKS
#include <sdl3/sdl.h>
#include <sdl3/sdl_main.h>

SDL_Window* window;
SDL_Renderer* renderer;

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{

}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char argv[])
{
        if(!SDL_Init(SDL_INIT_VIDEO))
        {
            SDL_Log("Error initializing SDL: %s", SDL_GetError());
        }
        return SDL_APP_FAILURE;
        window = SDL_CreateWindow("Snake Game toi yeu", 900, 800, NULL);
        if(!window)
        {
            SDL_Log("Error creating window: %s", SDL_GetError());
        }
        renderer = SDL_CreateRenderer(window, NULL);
        if(!renderer)
        {
            SDL_Log("Error creating renderer: %s", SDL_GetError());
        }
}
