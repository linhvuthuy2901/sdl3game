#include "SDL3/SDL_init.h"
#include "SDL3/SDL_oldnames.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_scancode.h"
#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_video.h"
#include "sdl3/SDL_events.h"
#include "sdl3/SDL_render.h"
#include <cstddef>
#define SDL_MAIN_USE_CALLBACKS
#include <sdl3/sdl.h>
#include <sdl3/sdl_main.h>
#include <vector>
using namespace std;

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

typedef struct
{
int x,y;
int w,h;
}Object; 

vector <Object> body;

Uint32 lastime=0;
int timedelay=150;

int length=3;

enum Direction {LEFT,RIGHT,UP,DOWN};
Direction direction=RIGHT;

const int GRID_SIZE=40;

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
        for (int i=length-1;i>=0;i--)
    {
        body.push_back({360,280,GRID_SIZE,GRID_SIZE});
    }
        
        return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if(event->type==SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;//thanh cong co the thoat
    }
    if(event->type==SDL_EVENT_KEY_DOWN)
    {
        switch(event->key.scancode)
        {
            case SDL_SCANCODE_DOWN:
            {   
                if(direction!=UP)
                {direction=DOWN;}
                break;
            }
            case SDL_SCANCODE_UP:
            {
                if(direction!=DOWN)
                {direction=UP;}
                break;
            }
            case SDL_SCANCODE_LEFT:
            {
                if(direction!=RIGHT)
                {direction=LEFT;}
                break;
            }
            case SDL_SCANCODE_RIGHT:
            {
                if(direction!=LEFT)
                {direction=RIGHT;}
                break;
            }
            default:
            {
                break;
            } 
        }
    }
    return SDL_APP_CONTINUE;  
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    SDL_SetRenderDrawColor(renderer,255, 182, 193, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,255, 105, 180, 0);
    for (int x = 0 ; x < 800; x += GRID_SIZE)
    {
        SDL_RenderLine(renderer, x, 0, x, 600);
    }
    for (int y = 0 ; y < 600 ; y += GRID_SIZE)
    {
        SDL_RenderLine(renderer, 0, y, 800, y);
    }

    Uint32 currentime=SDL_GetTicks();
    if(currentime-lastime>=timedelay)
        {
        lastime=currentime;
        for (int i=length-1;i>=0;i--)
        {
            if(i!=0)
            body[i]=body[i-1];
        }
        if(direction==UP)
            {
            body[0].y-=GRID_SIZE;
            }
        if(direction==DOWN)
            {
            body[0].y+=GRID_SIZE;
            }
        if(direction==RIGHT)
            {
            body[0].x+=GRID_SIZE;
            }
        if(direction==LEFT)
            {
            body[0].x-=GRID_SIZE;
            }
        }
        for (int i=length-1;i>=0;i--)
        {
            if(i==0)
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            }
             SDL_FRect rect1 ={(float)body[i].x,(float)body[i].y,(float)body[i].w,(float)body[i].h};
             SDL_RenderFillRect(renderer, &rect1);
        }
            SDL_RenderPresent(renderer);
        return SDL_APP_CONTINUE;
}
