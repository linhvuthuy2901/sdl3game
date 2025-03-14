#include "SDL3/SDL_init.h"
#include "SDL3/SDL_oldnames.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_scancode.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_video.h"
#include "sdl3/SDL_events.h"
#include "sdl3/SDL_render.h"
#include <algorithm>
#include <cstddef>
#define SDL_MAIN_USE_CALLBACKS
#include <sdl3/sdl.h>
#include <sdl3/sdl_main.h>
#include <vector>
using namespace std;
#include <SDL3_image/SDL_image.h>
#include <cstdlib>
#include <ctime>

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *tex;
SDL_Surface *bmp;

const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 1000;

SDL_FRect destRect = {400.0f, 300.0f, 200.0f, 100.0f};
SDL_FRect srcRect = {0.0f, 0.0f, 0.0f, 0.0f};

int increasetime = 30;
int consttime = 150;

typedef struct {
  int x, y;
  int w, h;
} Object;

bool mark = false;
bool gameend = false;
bool click = false;

Object Food;
int countf = 0;
vector<Object> body;

Uint32 lastime = 0;
Uint32 lastimeeatfood = 0;
int timedelay = consttime;

int length = 3;

enum Direction { LEFT, RIGHT, UP, DOWN };
Direction direction = RIGHT;

const int GRID_SIZE = 40;

int randomy() { return (rand() % (WINDOW_HEIGHT / GRID_SIZE)) * GRID_SIZE; }
int randomx() { return (rand() % (WINDOW_WIDTH / GRID_SIZE)) * GRID_SIZE; }

void food(); 

void restartGame() {
  SDL_SetRenderDrawColor(renderer, 255, 182, 193, 255);
  SDL_RenderClear(renderer);
  
  SDL_SetRenderDrawColor(renderer, 255, 105, 180, 0);
  for (int x = 0; x < WINDOW_WIDTH; x += GRID_SIZE) {
    SDL_RenderLine(renderer, x, 0, x, WINDOW_HEIGHT);
  }
  for (int y = 0; y < WINDOW_HEIGHT; y += GRID_SIZE) {
    SDL_RenderLine(renderer, 0, y, WINDOW_WIDTH, y);
  }
  
  for (int i = length - 1; i >= 0; i--) {
    if (i == 0) {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    } else {
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    }
    SDL_FRect rect1 = {(float)body[i].x, (float)body[i].y, (float)body[i].w, (float)body[i].h};
    SDL_RenderFillRect(renderer, &rect1);
  }
  
  food(); 
  
  if (tex) {
    SDL_RenderTexture(renderer, tex, &srcRect, &destRect);
    SDL_Log("Rendering restart texture at %.0f, %.0f", destRect.x, destRect.y);
  } else {
    SDL_Log("Texture is null!");
  }
  SDL_RenderPresent(renderer);
}

void food() {
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
  SDL_FRect rect3 = {(float)Food.x, (float)Food.y, (float)GRID_SIZE, (float)GRID_SIZE};
  SDL_RenderFillRect(renderer, &rect3);
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  SDL_DestroyRenderer(renderer);
  renderer = NULL;
  SDL_DestroyWindow(window);
  window = NULL;
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
  SDL_DestroySurface(bmp);
  SDL_DestroyTexture(tex);
}

void random2() {
  Food.x = randomx();
  Food.y = randomy();
}

void touch() {
  random2();
  food();
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Error initializing SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  window = SDL_CreateWindow("Snake Game toi yeu", WINDOW_WIDTH, WINDOW_HEIGHT, NULL);
  if (!window) {
    SDL_Log("Error creating window: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  renderer = SDL_CreateRenderer(window, NULL);
  if (!renderer) {
    SDL_Log("Error creating renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  bmp = SDL_LoadBMP("restart.bmp");
  if (bmp == nullptr) {
    SDL_Log("Error loading restart.bmp: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  srcRect.w = (float)bmp->w;
  srcRect.h = (float)bmp->h;
  SDL_Log("Loaded restart.bmp: %dx%d", bmp->w, bmp->h);
  
  tex = SDL_CreateTextureFromSurface(renderer, bmp);
  if (tex == nullptr) {
    SDL_Log("Error creating texture: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  for (int i = length - 1; i >= 0; i--) {
    body.push_back({360, 280, GRID_SIZE, GRID_SIZE});
  }
  srand(time(0));
  Food.x = randomx();
  Food.y = randomy();
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  }
  if (event->type == SDL_EVENT_KEY_DOWN && !gameend) {
    switch (event->key.scancode) {
    case SDL_SCANCODE_A: {
      mark = true;
      break;
    }
    case SDL_SCANCODE_DOWN: {
      if (direction != UP) {
        direction = DOWN;
      }
      break;
    }
    case SDL_SCANCODE_UP: {
      if (direction != DOWN) {
        direction = UP;
      }
      break;
    }
    case SDL_SCANCODE_LEFT: {
      if (direction != RIGHT) {
        direction = LEFT;
      }
      break;
    }
    case SDL_SCANCODE_RIGHT: {
      if (direction != LEFT) {
        direction = RIGHT;
      }
      break;
    }
    default: {
      break;
    }
    }
  }
  if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN && gameend) {
    int mouseX = event->button.x;
    int mouseY = event->button.y;
    if (mouseX >= destRect.x && mouseX <= destRect.x + destRect.w &&
        mouseY >= destRect.y && mouseY <= destRect.y + destRect.h) {
      click = true;
      SDL_Log("Click to continue %d, %d", mouseX, mouseY);
    }
  }
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  SDL_SetRenderDrawColor(renderer, 255, 182, 193, 255);
  SDL_RenderClear(renderer);
  
  SDL_SetRenderDrawColor(renderer, 255, 105, 180, 0);
  for (int x = 0; x < WINDOW_WIDTH; x += GRID_SIZE) {
    SDL_RenderLine(renderer, x, 0, x, WINDOW_HEIGHT);
  }
  for (int y = 0; y < WINDOW_HEIGHT; y += GRID_SIZE) {
    SDL_RenderLine(renderer, 0, y, WINDOW_WIDTH, y);
  }

  if (!gameend) {
    Uint32 currentime = SDL_GetTicks();

    if (currentime - lastime >= timedelay) {
      lastime = currentime;
      for (int i = length - 1; i >= 0; i--) {
        if (i != 0)
          body[i] = body[i - 1];
      }
      if (direction == UP) {
        body[0].y -= GRID_SIZE;
      }
      if (direction == DOWN) {
        body[0].y += GRID_SIZE;
      }
      if (direction == RIGHT) {
        body[0].x += GRID_SIZE;
      }
      if (direction == LEFT) {
        body[0].x -= GRID_SIZE;
      }
    }

    food();
    if (body[0].x == Food.x && body[0].y == Food.y) {
      touch();
      countf++;
      length++;
      body.push_back({body[length - 2].x, body[length - 2].y, GRID_SIZE, GRID_SIZE});
    }
    for (int i = 1; i < length; i++) {
      if (body[i].x == Food.x && body[i].y == Food.y) {
        touch();
      }
    }
    if (countf == 5 && timedelay >= 100) {
      timedelay -= increasetime;
      countf = 0;
    }

    for (int i = length - 1; i >= 0; i--) {
      if (i == 0) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
      } else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
      }
      SDL_FRect rect1 = {(float)body[i].x, (float)body[i].y, (float)body[i].w, (float)body[i].h};
      SDL_RenderFillRect(renderer, &rect1);
    }

    if (((currentime - lastimeeatfood >= 5000) && mark == true) || 
        (currentime < 5000) && mark == true) {
      lastimeeatfood = currentime;
      for (int i = length - 1; i > 0; i--) {
        body[i] = body[i - 1];
      }
      if (direction == UP && body[0].y < WINDOW_HEIGHT - 2 * GRID_SIZE) {
        body[0].y -= 2 * GRID_SIZE;
      } else if (direction == DOWN && body[0].y > 3 * GRID_SIZE) {
        body[0].y += 2 * GRID_SIZE;
      } else if (direction == RIGHT && body[0].x < WINDOW_WIDTH - GRID_SIZE) {
        body[0].x += 2 * GRID_SIZE;
      } else if (direction == LEFT && body[0].x > 2 * GRID_SIZE) {
        body[0].x -= 2 * GRID_SIZE;
      }
      mark = false;
    } else if ((currentime - lastimeeatfood < 5000) && mark == true) {
      mark = false;
    }

    if (body[0].x == -GRID_SIZE && direction == LEFT) {
      body[0].x = WINDOW_WIDTH - GRID_SIZE;
    }
    if (body[0].y == -GRID_SIZE && direction == UP) {
      body[0].y = WINDOW_HEIGHT - GRID_SIZE;
    }
    if (body[0].x == WINDOW_WIDTH && direction == RIGHT) {
      body[0].x = 0;
    }
    if (body[0].y == WINDOW_HEIGHT && direction == DOWN) {
      body[0].y = 0;
    }

    for (int i = 3; i < length; i++) {
      if (body[0].x == body[i].x && body[0].y == body[i].y) {
        gameend = true;
      }
    }
  }

  if (gameend == true) {
    restartGame();
    if (click == true) {
      timedelay = consttime;
      body.erase(body.begin() + 3, body.end());
      length = 3;
      for (int i = 0; i < 3; i++) {
        body[i].x = 360;
        body[i].y = 280;
      }
      direction = RIGHT;
      countf = 0;
      gameend = false;
      click = false;
      random2();
    }
    return SDL_APP_CONTINUE;
  }

  SDL_RenderPresent(renderer);
  return SDL_APP_CONTINUE;
}
