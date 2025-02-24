#include "SDL3/SDL_init.h"
#include "SDL3/SDL_oldnames.h"
#include "SDL3/SDL_video.h"
#include "sdl3/SDL_events.h"
#include "sdl3/SDL_render.h"
#include <cstddef>
#define SDL_MAIN_USE_CALLBACKS
#include <sdl3/sdl.h>
#include <sdl3/sdl_main.h>

SDL_Window* window;
SDL_Renderer* renderer;

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window=NULL;
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
        if(!SDL_Init(SDL_INIT_VIDEO))
        {
            SDL_Log("Error initializing SDL: %s", SDL_GetError());
            return SDL_APP_FAILURE;
        }
        window = SDL_CreateWindow("Snake Game toi yeu",800,600,NULL);
   
        if(!window)
        {
            SDL_Log("Error creating window: %s", SDL_GetError());
            return SDL_APP_FAILURE;
        }
        
        renderer = SDL_CreateRenderer(window, NULL);
        if(!renderer)
        {
            SDL_Log("Error creating renderer: %s", SDL_GetError());
            return SDL_APP_FAILURE;
        }
        return SDL_APP_CONTINUE;
}
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if(event->type==SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;//thanh cong co the thoat
    }
    return SDL_APP_CONTINUE;  
}
SDL_AppResult SDL_AppIterate(void *appstate)
{
    SDL_SetRenderDrawColor(renderer,255, 182, 193, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    
    
    SDL_SetRenderDrawColor(renderer,0, 182, 193, 255);
    for (int x = 0 ; x < 800; x += 40)
    {
        SDL_RenderLine(renderer, x, 0, x, 600);
    }
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer,0, 182, 193, 255);
    for (int y = 0 ; y < 600 ; y += 40)
    {
        SDL_RenderLine(renderer, 0, y, 800, y);
    }
    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE;
}
