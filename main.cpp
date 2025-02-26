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
#include <ctime>
#include <cstdlib>

SDL_Window* window;
SDL_Renderer* renderer;

const int WINDOW_HEIGHT = 920;
const int WINDOW_WIDTH= 720;


typedef struct
{
int x,y;
int w,h;
}Object; 

Object Food;

vector <Object> body;

Uint32 lastime=0;
int timedelay=150;

int length=3;

enum Direction {LEFT,RIGHT,UP,DOWN};
Direction direction=RIGHT;

const int GRID_SIZE=40;

int randomy()
{
    return (rand()%(WINDOW_HEIGHT/GRID_SIZE))*GRID_SIZE;
}

int randomx()
{
    return (rand()%(WINDOW_WIDTH/GRID_SIZE))*GRID_SIZE;
}

void food()
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_FRect rect3 ={(float)Food.x,(float)Food.y,(float)GRID_SIZE,(float)GRID_SIZE};
    SDL_RenderFillRect(renderer, &rect3);
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window=NULL;
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
void random2()
{
    Food.x=randomx();
    Food.y=randomy();
}

void touch()
{
    random2();
    food();
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
        if(!SDL_Init(SDL_INIT_VIDEO))
        {
            SDL_Log("Error initializing SDL: %s", SDL_GetError());
            return SDL_APP_FAILURE;
        }
        window = SDL_CreateWindow("Snake Game toi yeu",WINDOW_WIDTH,WINDOW_HEIGHT,NULL);
   
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
    srand(time(0 ));
    Food.x=randomx();
    Food.y=randomy();
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
    for (int x = 0 ; x < WINDOW_WIDTH; x += GRID_SIZE)
    {
        SDL_RenderLine(renderer, x, 0, x, WINDOW_HEIGHT);
    }
    for (int y = 0 ; y < WINDOW_HEIGHT ; y += GRID_SIZE)
    {
        SDL_RenderLine(renderer, 0, y, WINDOW_WIDTH, y);
    }
    
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    
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
            body[0].y -= GRID_SIZE;
            }
        if(direction==DOWN)
            {
            body[0].y += GRID_SIZE;
            }
        if(direction == RIGHT)
            {
            body[0].x+=GRID_SIZE;
            }
        if(direction == LEFT)
            {
            body[0].x-=GRID_SIZE;
            }
        }
        if(currentime>=0)
    {
            {
                food();
if (body[0].x == Food.x && body[0].y == Food.y)
            {
                touch();
                length++;
                body.push_back({body[length-2].x,body[length-2].y,GRID_SIZE,GRID_SIZE});
            }
            }
    }
        for (int i = length-1; i >= 0; i--)
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
            if(body[0].x==-GRID_SIZE&&direction==LEFT)
            {
                body[0].x=WINDOW_WIDTH-GRID_SIZE;
            }
            if(body[0].y==-GRID_SIZE&&direction==UP)
            {
                body[0].y=WINDOW_HEIGHT-GRID_SIZE;
            }
            if(body[0].x==WINDOW_WIDTH&&direction==RIGHT)
            {
                body[0].x=0;
            }
            if(body[0].y==WINDOW_HEIGHT&&direction==DOWN)
            {
                body[0].y=0;
            }
        return SDL_APP_CONTINUE;
}
