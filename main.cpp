#include "sdl3/SDL_init.h"
#include "sdl3/SDL_log.h"
#include "sdl3/SDL_oldnames.h"
#include "sdl3/SDL_rect.h"
#include "sdl3/SDL_render.h"
#include "sdl3/SDL_surface.h"
#include <algorithm>
#include <cstddef>
#define SDL_MAIN_USE_CALLBACKS
#include <sdl3/sdl.h>
#include <sdl3/sdl_main.h>
#include <vector>
using namespace std;
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstdlib>
#include <ctime>

const int GRID_SIZE = 40;

float wallx[] = {GRID_SIZE * 8, GRID_SIZE * 7, GRID_SIZE*2};
float wally[] = {GRID_SIZE * 10, GRID_SIZE * 7, GRID_SIZE * 4};
float wallw[] = {GRID_SIZE * 1, GRID_SIZE*10, GRID_SIZE * 1};
float wallh[] = {GRID_SIZE * 5, GRID_SIZE , GRID_SIZE * 4};

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *tex;
SDL_Surface *bmp;
SDL_Texture *tex2;
SDL_Surface *bmp2;
SDL_Texture *tex3;
SDL_Surface *bmp3;
SDL_Texture *tex4;
SDL_Surface *bmp4;
SDL_Texture *tex5;
SDL_Surface *bmp5;
SDL_Texture *tex6;
SDL_Surface *bmp6;
SDL_Texture *tex7;
SDL_Surface *bmp7;
SDL_Texture *tex8;
SDL_Surface *bmp8;
SDL_Texture *tex9;
SDL_Surface *bmp9;

SDL_Surface *texsurface;
SDL_Texture *textTexture;
const char *text = "Your score : ";

const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 1000;

SDL_FRect destRect = {310.0f, 450.0f, 370.0f, 300.0f}; /// RESTART
SDL_FRect srcRect = {0.0f, 0.0f, 0.0f, 0.0f};
SDL_FRect destRect2 = {400.0f, 300.0f, 200.0f, 100.0f};

int increasetime = 30;
int directionwall = false;
int consttime = 150;
int nowtime = 0;

typedef struct {
  int x, y;
  int w, h;
} Object;

bool mark = false;
bool gameend = false;
bool click = false;
bool start = true;
bool started = false;
bool vavaotuong = false;

Object Food;
int countf = 0;
int countf2 = 1;
vector<Object> body;
Object wall;
Object wallDoNotRun;

Uint32 lastime = 0;
Uint32 lastimeeatfood = 0;
int timedelay = consttime;

int length = 3;

enum Direction { LEFT, RIGHT, UP, DOWN };
Direction direction = RIGHT;

int randomy() { return (rand() % (WINDOW_HEIGHT / GRID_SIZE)) * GRID_SIZE; }
int randomx() { return (rand() % (WINDOW_WIDTH / GRID_SIZE)) * GRID_SIZE; }

void food();

void restartGame() {
  if (tex) {
    SDL_RenderTexture(renderer, tex, &srcRect, &destRect2);
    SDL_Log("Rendering restart texture at %.0f, %.0f", destRect2.x,
            destRect2.y);
  } else {
    SDL_Log("Texture is null!");
  }
  SDL_RenderPresent(renderer);
}

void food() {
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
  SDL_FRect rect3 = {(float)Food.x, (float)Food.y, (float)GRID_SIZE,
                     (float)GRID_SIZE};
  SDL_RenderTexture(renderer, tex6, NULL, &rect3);
}

void drawwall() {
  SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);
  SDL_FRect rect3 = {(float)wall.x, (float)wall.y, (float)GRID_SIZE,
                     (float)GRID_SIZE};
  SDL_RenderTexture(renderer, tex8, NULL, &rect3);
}

void drawwallDoNotRun() {
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
  SDL_FRect rectwall1 = {wallx[0], wally[0], wallw[0], wallh[0]};
  SDL_RenderTexture(renderer, tex9, NULL, &rectwall1);
  SDL_FRect rectwall2 = {wallx[1], wally[1], wallw[1], wallh[1]};
  SDL_RenderTexture(renderer, tex9, NULL, &rectwall2);
  SDL_FRect rectwall3 = {wallx[2], wally[2], wallw[2], wallh[2]};
  SDL_RenderTexture(renderer, tex9, NULL, &rectwall3);
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  SDL_DestroyRenderer(renderer);
  renderer = NULL;
  SDL_DestroyWindow(window);
  window = NULL;
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
  SDL_DestroySurface(bmp);
  SDL_DestroyTexture(tex);
  SDL_DestroySurface(bmp2);
  SDL_DestroyTexture(tex2);
  SDL_DestroySurface(bmp3);
  SDL_DestroyTexture(tex3);
  SDL_DestroySurface(bmp4);
  SDL_DestroyTexture(tex4);
  SDL_DestroySurface(bmp5);
  SDL_DestroyTexture(tex5);
  SDL_DestroySurface(bmp6);
  SDL_DestroyTexture(tex6);
  SDL_DestroySurface(bmp7);
  SDL_DestroyTexture(tex7);
  SDL_DestroySurface(bmp8);
  SDL_DestroyTexture(tex8);
}

void random2() {
  Food.x = randomx();
  Food.y = randomy();
  for (int i=0;i<3;i++)
  {
    if(Food.x==wallx[i])
    {
      Food.x=randomx();
    }
    if(Food.y==wally[i])
    {
      Food.y=randomy();
    }
  }
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
  window =
      SDL_CreateWindow("Snake Game toi yeu", WINDOW_WIDTH, WINDOW_HEIGHT, NULL);
  if (!window) {
    SDL_Log("Error creating window: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  renderer = SDL_CreateRenderer(window, NULL);
  if (!renderer) {
    SDL_Log("Error creating renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  // RESTART
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
  // background sau khi bam start
  bmp2 = SDL_LoadBMP("backgroundsau.bmp");
  if (bmp2 == nullptr) {
    SDL_Log("Error loading restart.bmp2: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  tex2 = SDL_CreateTextureFromSurface(renderer, bmp2);
  if (tex2 == nullptr) {
    SDL_Log("Error creating texture: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  // START BUTTON
  bmp3 = SDL_LoadBMP("batdau.bmp");
  if (bmp3 == nullptr) {
    SDL_Log("Error loading restart.bmp2: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  tex3 = SDL_CreateTextureFromSurface(renderer, bmp3);
  if (tex3 == nullptr) {
    SDL_Log("Error creating texture: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  // ĐỒ HOẠ ĐẦU RẮN
  bmp4 = SDL_LoadBMP("head.bmp");
  if (bmp4 == nullptr) {
    SDL_Log("Error loading restart.bmp2: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  tex4 = SDL_CreateTextureFromSurface(renderer, bmp4);
  if (tex4 == nullptr) {
    SDL_Log("Error creating texture: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  // ĐỒ HOẠ THÂN RẮN
  bmp5 = SDL_LoadBMP("body.bmp");
  if (bmp5 == nullptr) {
    SDL_Log("Error loading restart.bmp2: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  tex5 = SDL_CreateTextureFromSurface(renderer, bmp5);
  if (tex5 == nullptr) {
    SDL_Log("Error creating texture: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  // ĐỒ HOẠ THỨC ĂN
  bmp6 = SDL_LoadBMP("food.bmp");
  if (bmp6 == nullptr) {
    SDL_Log("Error loading restart.bmp2: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  tex6 = SDL_CreateTextureFromSurface(renderer, bmp6);
  if (tex6 == nullptr) {
    SDL_Log("Error creating texture: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  // BACKGROUND TRƯỚC KHI BẤM START
  bmp7 = SDL_LoadBMP("backgroundbandau.bmp");
  if (bmp7 == nullptr) {
    SDL_Log("Error loading restart.bmp2: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  tex7 = SDL_CreateTextureFromSurface(renderer, bmp7);
  if (tex7 == nullptr) {
    SDL_Log("Error creating texture: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  // WALL
  bmp8 = SDL_LoadBMP("wall.bmp");
  if (bmp8 == nullptr) {
    SDL_Log("Error loading restart.bmp2: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  tex8 = SDL_CreateTextureFromSurface(renderer, bmp8);
  if (tex8 == nullptr) {
    SDL_Log("Error creating texture: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

// WALLCODINH
  bmp9 = SDL_LoadBMP("wallcodinh.bmp");
  if (bmp9 == nullptr) {
    SDL_Log("Error loading restart.bmp2: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  tex9 = SDL_CreateTextureFromSurface(renderer, bmp8);
  if (tex9 == nullptr) {
    SDL_Log("Error creating texture: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  // Khoi tao TTF
  if (!TTF_Init()) {
    SDL_Log("Can not down ttf:%s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  TTF_Font *font = TTF_OpenFont("font_pixel.ttf", 24);
  if (!font) {
    SDL_Log("Can not down font:%s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  SDL_Color textColor = {255, 255, 255, 255};
  texsurface = TTF_RenderText_Solid(font, text, strlen(text), textColor);
  textTexture = SDL_CreateTextureFromSurface(renderer, texsurface);
  for (int i = length - 1; i >= 0; i--) {
    body.push_back({40, 40, GRID_SIZE, GRID_SIZE});
  }

  srand(time(0));
  Food.x = randomx();
  Food.y = randomy();
  wall.x = randomx();
  wall.y = randomy();
  if (wall.y == 40) {
    wall.y = randomy();
  }
  for (int i=0;i<3;i++)
  {
    if(Food.x==wallx[i])
    {
      Food.x=randomx();
    }
    if(Food.y==wally[i])
    {
      Food.y=randomy();
    }
  }
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
  if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN && (gameend)) {
    int mouseX = event->button.x;
    int mouseY = event->button.y;
    if (mouseX >= destRect2.x && mouseX <= destRect2.x + destRect2.w &&
        mouseY >= destRect2.y && mouseY <= destRect2.y + destRect2.h) {
      click = true;

      SDL_Log("Click to continue %d, %d", mouseX, mouseY);
    }
  }
  if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN && (gameend)) {
    int mouseX = event->button.x;
    int mouseY = event->button.y;
    if (mouseX >= destRect2.x && mouseX <= destRect2.x + destRect2.w &&
        mouseY >= destRect2.y && mouseY <= destRect2.y + destRect2.h) {
      click = true;

      SDL_Log("Click to continue %d, %d", mouseX, mouseY);
    }
  }
  if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN && (start)) {
    int mouseX = event->button.x;
    int mouseY = event->button.y;
    if (mouseX >= destRect.x && mouseX <= destRect.x + destRect.w &&
        mouseY >= destRect.y && mouseY <= destRect.y + destRect.h) {
      start = false;
      started = true;
      SDL_Log("Click to continue %d, %d", mouseX, mouseY);
    }
  }
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {

  SDL_RenderClear(renderer);
  if (started == false) {
    SDL_RenderTexture(renderer, tex7, NULL, NULL);
    SDL_RenderTexture(renderer, tex3, &srcRect, &destRect);
    SDL_RenderPresent(renderer);
  }

  if (started == true) {
    SDL_FRect dst_rect;
    SDL_RenderTexture(renderer, textTexture, NULL, &dst_rect);
    SDL_RenderTexture(renderer, tex2, NULL, NULL);
    if (vavaotuong == false) {
      drawwallDoNotRun();
    }

    dst_rect.x = ((float)(90));
    dst_rect.y = (float)(100);
    dst_rect.w = (float)200;
    dst_rect.h = (float)30;
    SDL_RenderTexture(renderer, textTexture, NULL, &dst_rect);
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
      if (body[0].x)
        if (body[0].x == Food.x && body[0].y == Food.y) {
          touch();
          countf++;
          length++;
          countf2++;
          body.push_back(
              {body[length - 2].x, body[length - 2].y, GRID_SIZE, GRID_SIZE});
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
        SDL_FRect rect1 = {(float)body[i].x, (float)body[i].y, (float)body[i].w,
                           (float)body[i].h};
        if (i == 0) {
          SDL_RenderTexture(renderer, tex4, NULL, &rect1);
        } else {
          SDL_RenderTexture(renderer, tex5, NULL, &rect1);
        }
      }

      if (countf2 % 4 == 0) {
        wall.x = randomx();
        wall.y = randomy();
        if ((wall.x == body[0].x || wall.y == body[0].y)) {
          wall.x = randomx();
          wall.y = randomy();
        }
        countf2 = 1;
      }
      //DRAW TƯỜNG CỐ ĐỊNH
      for (int i = 0; i < 3; i++) {
        if (body[0].x >= wallx[i] && body[0].x < wallx[i] + wallw[i] &&
            body[0].y >= wally[i] && body[0].y < wally[i] + wallh[i]) {
          gameend = true;
          vavaotuong = true;
        }
      }

      if (((currentime - lastimeeatfood >= 5000) && mark == true) ||
          (currentime < 5000) && mark == true) {
        lastimeeatfood = currentime;
        for (int i = length - 1; i > 0; i--) {
          body[i] = body[i - 1];
        }
        if (direction == UP && body[0].y < WINDOW_HEIGHT - 2 * GRID_SIZE) {
          body[0].y -= 2 * GRID_SIZE;
        } else if (direction == DOWN && body[0].y > 4 * GRID_SIZE) {
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
      drawwall();
      if (currentime - nowtime >= 69) {
        nowtime = currentime;
        if (directionwall == false) {
          wall.x -= GRID_SIZE;
        }
        if (wall.x == -GRID_SIZE) {
          directionwall = true;
        }
        if (directionwall == true) {
          wall.x += GRID_SIZE;
        }
        if (wall.x == WINDOW_WIDTH) {
          directionwall = false;
        }
      }
      if (body[0].x == wall.x && body[0].y == wall.y) {
        gameend = true;
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
          body[i].x = 40;
          body[i].y = 40;
        }
        wall.x = randomx();
        wall.y = randomy();
        if (wall.y == 280) {
          wall.y = randomy();
        }
        direction = RIGHT;
        countf = 0;
        countf2 = 1;
        gameend = false;
        click = false;
        random2();
        vavaotuong = false;
      }
      return SDL_APP_CONTINUE;
    }
    SDL_RenderPresent(renderer);
  }
  return SDL_APP_CONTINUE;
}
