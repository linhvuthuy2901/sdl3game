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
#include <string>
#include <SDL3/SDL_audio.h>


const int GRID_SIZE = 40;
const int WALLSIZE = 7;
float wallx[] = {GRID_SIZE * 8,  GRID_SIZE * 7, GRID_SIZE * 2, GRID_SIZE * 18,
                 GRID_SIZE * 16, GRID_SIZE * 3, GRID_SIZE * 16};
float wally[] = {GRID_SIZE * 13, GRID_SIZE * 7,  GRID_SIZE * 4, GRID_SIZE * 2,
                 GRID_SIZE * 8,  GRID_SIZE * 11, GRID_SIZE * 16};
float wallw[] = {GRID_SIZE * 1, GRID_SIZE * 10, GRID_SIZE * 1, GRID_SIZE,
                 GRID_SIZE,     GRID_SIZE * 11, GRID_SIZE * 7};
float wallh[] = {GRID_SIZE * 5, GRID_SIZE, GRID_SIZE * 4, GRID_SIZE * 8,
                 GRID_SIZE * 7, GRID_SIZE, GRID_SIZE};

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
SDL_Texture *tex10;
SDL_Surface *bmp10;

SDL_Surface *scoreSurface;
SDL_Texture *scoreTexture;
SDL_Surface *highScoreSurface;
SDL_Texture *highScoreTexture;
SDL_Surface *LevelSurface;
SDL_Texture *LevelTexture;

const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 1000;

SDL_FRect destRect = {310.0f, 450.0f, 370.0f, 300.0f}; /// RESTART
SDL_FRect srcRect = {0.0f, 0.0f, 0.0f, 0.0f};
SDL_FRect destRect2 = {400.0f, 300.0f, 200.0f, 100.0f};
SDL_FRect destRect3 = {240.0f, -20.0f, 500.0f, 400.0f};


int increasetime = 30;
int directionwall = false;
int consttime = 150;
int nowtime = 0;
int uplevel=4;//Sau khi ăn này mồi thì tăng 1 level

int score = 0;
int highScore = 0;
int level=1;

// TỌA ĐỘ CỦA PHÙ THỦY
int toadox;
int toadoy;

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
Direction pendingDirection = RIGHT;

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

SDL_FRect rw1, rw2, rw3, rw4, rw5, rw6, rw7;
SDL_FRect rectwall[] = {rw1, rw2, rw3, rw4, rw5, rw6, rw7};
void drawwallDoNotRun() {
  for (int i = 0; i < WALLSIZE; i++) {
    rectwall[i] = {wallx[i], wally[i], wallw[i], wallh[i]};
    SDL_RenderTexture(renderer, tex9, NULL, &rectwall[i]);
  }
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
  SDL_DestroySurface(scoreSurface);
  SDL_DestroyTexture(scoreTexture);
  SDL_DestroySurface(highScoreSurface);
  SDL_DestroyTexture(highScoreTexture);
  SDL_DestroySurface(LevelSurface);
  SDL_DestroyTexture(LevelTexture);
}


void random2() {
  Food.x = randomx();
  Food.y = randomy();
  for (int i = 0; i < WALLSIZE; i++) {
    if (Food.x >= wallx[i] && Food.y >= wally[i] &&
        Food.x <= wallx[i] + wallw[i] && Food.y <= wally[i] + wallh[i]) {
      Food.x = randomx();
      Food.y = randomy();
    }
  }
}

void touch() {
  random2();
  food();
  score += 10;
  if (score > highScore)
    highScore = score;
}


SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Error initializing SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  window =
      SDL_CreateWindow("Snake Game - INT2215_7 - 24021548", WINDOW_WIDTH, WINDOW_HEIGHT, NULL);
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
  tex9 = SDL_CreateTextureFromSurface(renderer, bmp9);
  if (tex9 == nullptr) {
    SDL_Log("Error creating texture: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  //GAMEOVER
  bmp10 = SDL_LoadBMP("gameover.bmp");
  if (bmp10 == nullptr) {
    SDL_Log("Error loading restart.bmp2: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  tex10 = SDL_CreateTextureFromSurface(renderer, bmp10);
  if (tex10 == nullptr) {
    SDL_Log("Error creating texture: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  // Khởi tạo TTF
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

  // Khởi tạo  điểm số
  string scoreText = "Your Score: " + to_string(score);
  scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(),
                                      strlen(scoreText.c_str()), textColor);
  scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);

  // Khởi tạo  điểm cao nhất
  string highScoreText = "High Score: " + to_string(highScore);
  highScoreSurface = TTF_RenderText_Solid(
      font, highScoreText.c_str(), strlen(highScoreText.c_str()), textColor);
  highScoreTexture = SDL_CreateTextureFromSurface(renderer, highScoreSurface);

  //Khởi tạo level
string LevelText = "Level : " + to_string(level);
  LevelSurface = TTF_RenderText_Solid(
      font, highScoreText.c_str(), strlen(LevelText.c_str()), textColor);
  LevelTexture = SDL_CreateTextureFromSurface(renderer, LevelSurface);

  for (int i = length - 1; i >= 0; i--) {
    body.push_back({40, 40, GRID_SIZE, GRID_SIZE});
  }

  srand(time(0));
  toadox = randomx();
  toadoy = randomy();
  Food.x = randomx();
  Food.y = randomy();
  wall.x = randomx();
  wall.y = randomy();
  if (wall.y == body[0].y) {
    wall.y = randomy();
  }
  for (int i = 0; i < WALLSIZE; i++) {
    if (Food.x >= wallx[i] && Food.y >= wally[i] &&
        Food.x <= wallx[i] + wallw[i] && Food.y <= wally[i] + wallh[i]) {
      Food.x = randomx();
      Food.y = randomy();
    }
  }
  TTF_CloseFont(font);
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
        pendingDirection = DOWN;
      }
      break;
    }
    case SDL_SCANCODE_UP: {
      if (direction != DOWN) {
        pendingDirection = UP;
      }
      break;
    }
    case SDL_SCANCODE_LEFT: {
      if (direction != RIGHT) {
        pendingDirection = LEFT;
      }
      break;
    }
    case SDL_SCANCODE_RIGHT: {
      if (direction != LEFT) {
        pendingDirection = RIGHT;
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
    SDL_RenderTexture(renderer, tex2, NULL, NULL);
    if (vavaotuong == false) {
      drawwallDoNotRun();
    }
    

    TTF_Font *font = TTF_OpenFont("font_pixel.ttf", 24);
    SDL_Color textColor = {255, 255, 255, 255};
    string scoreText = "Your Score: " + to_string(score);
    if (scoreSurface)
      SDL_DestroySurface(scoreSurface);
    if (scoreTexture)
      SDL_DestroyTexture(scoreTexture);
    scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(),
                                        strlen(scoreText.c_str()), textColor);
    scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_FRect scoreRect = {90.0f, 70.0f, 200.0f, 30.0f};
    SDL_RenderTexture(renderer, scoreTexture, NULL, &scoreRect);

    string highScoreText = "High Score: " + to_string(highScore);
    if (highScoreSurface)
      SDL_DestroySurface(highScoreSurface);
    if (highScoreTexture)
      SDL_DestroyTexture(highScoreTexture);
    highScoreSurface = TTF_RenderText_Solid(
        font, highScoreText.c_str(), strlen(highScoreText.c_str()), textColor);
    highScoreTexture = SDL_CreateTextureFromSurface(renderer, highScoreSurface);
    SDL_FRect highScoreRect = {90.0f, 100.0f, 200.0f, 30.0f};
    SDL_RenderTexture(renderer, highScoreTexture, NULL, &highScoreRect);

    string LevelText = "Level : " + to_string(level);
    if (LevelSurface)
      SDL_DestroySurface(LevelSurface);
    if (LevelTexture)
      SDL_DestroyTexture(LevelTexture);
    LevelSurface = TTF_RenderText_Solid(
        font, LevelText.c_str(), strlen(LevelText.c_str()), textColor);
    LevelTexture = SDL_CreateTextureFromSurface(renderer, LevelSurface);
    SDL_FRect LevelRect = {90.0f, 40.0f, 140.0f, 30.0f};
    SDL_RenderTexture(renderer, LevelTexture, NULL, &LevelRect);

    TTF_CloseFont(font);
      Uint32 currentime = SDL_GetTicks();

    if (!gameend) {

      if (currentime - lastime >= timedelay) {
        lastime = currentime;
        direction = pendingDirection;

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
      for (int i = 0; i < WALLSIZE; i++) {
        if (Food.x >= wallx[i] && Food.y >= wally[i] &&
            Food.x <= wallx[i] + wallw[i] && Food.y <= wally[i] + wallh[i]) {
          Food.x = randomx();
          Food.y = randomy();
        }
      }
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
      if (countf == uplevel && timedelay >= 80) {
        timedelay -= increasetime;
        countf = 0;
        level+=1;
        uplevel+=3;
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
      // DRAW TƯỜNG CỐ ĐỊNH
      for (int i = 0; i < WALLSIZE; i++) {
        if (body[0].x >= wallx[i] && body[0].x < wallx[i] + wallw[i] &&
            body[0].y >= wally[i] && body[0].y < wally[i] + wallh[i]) {
          gameend = true;
          vavaotuong = true;
        }
      }
      if ((currentime - lastimeeatfood >= 7000) && mark == true) {
        lastimeeatfood = currentime;
        
        for (int i = length - 1; i > 0; i--) {
          body[i] = body[i - 1];
        }
        if (direction == UP && body[0].y > 3 * GRID_SIZE) {
          body[0].y -= 3 * GRID_SIZE;
        } else if (direction == DOWN &&
                   body[0].y < WINDOW_HEIGHT - 3 * GRID_SIZE) {
          body[0].y += 3 * GRID_SIZE;
        } else if (direction == RIGHT &&
                   body[0].x < WINDOW_WIDTH - 2 * GRID_SIZE) {
          body[0].x += 3 * GRID_SIZE;
        } else if (direction == LEFT && body[0].x > 3 * GRID_SIZE) {
          body[0].x -= 3 * GRID_SIZE;
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
        vavaotuong = true;
      }
      for (int i = 3; i < length; i++) {
        if (body[0].x == body[i].x && body[0].y == body[i].y) {
          gameend = true;
          vavaotuong = true;
        }
      }
    }

    if (gameend == true) {
      SDL_RenderTexture(renderer, tex10, &srcRect, &destRect3); // Render gameover.bmp
      SDL_RenderTexture(renderer, tex, &srcRect, &destRect2); // Render restart button
      SDL_RenderPresent(renderer);
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
          lastimeeatfood = currentime;
          direction = RIGHT;
          pendingDirection = RIGHT;
          countf = 0;
          countf2 = 1;
          gameend = false;
          click = false;
          random2();
          vavaotuong = false;
          score = 0;
          uplevel = 4;
          level = 1;
          if (wall.y == 40) {
              wall.y = randomy();
          }
          for (int i = 0; i < WALLSIZE; i++) {
              if (Food.x >= wallx[i] && Food.y >= wally[i] &&
                  Food.x <= wallx[i] + wallw[i] && Food.y <= wally[i] + wallh[i]) {
                  Food.x = randomx();
                  Food.y = randomy();
              }
          }
      }
      return SDL_APP_CONTINUE;
  }
    SDL_RenderPresent(renderer);
  }
  return SDL_APP_CONTINUE;
}
