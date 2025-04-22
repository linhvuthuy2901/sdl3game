#include "resources.h"
#include "renderer.h"
#include "game.h"
#include "walls.h"
#include <cstdlib>
#include <ctime>

SDL_Window* window = nullptr;

void initResources() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Error initializing SDL: %s", SDL_GetError());
        return;
    }
    window = SDL_CreateWindow("Snake Game - INT2215_7 - 24021548", WINDOW_WIDTH, WINDOW_HEIGHT, NULL);
    if (!window) {
        SDL_Log("Error creating window: %s", SDL_GetError());
        return;
    }
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_Log("Error creating renderer: %s", SDL_GetError());
        return;
    }
    // RESTART
    bmp = SDL_LoadBMP("restart.bmp");
    if (bmp == nullptr) {
        SDL_Log("Error loading restart.bmp: %s", SDL_GetError());
        return;
    }
    srcRect.w = (float)bmp->w;
    srcRect.h = (float)bmp->h;
    SDL_Log("Loaded restart.bmp: %dx%d", bmp->w, bmp->h);
    tex = SDL_CreateTextureFromSurface(renderer, bmp);
    if (tex == nullptr) {
        SDL_Log("Error creating texture: %s", SDL_GetError());
        return;
    }
    // background sau khi bam start
    bmp2 = SDL_LoadBMP("backgroundsau.bmp");
    if (bmp2 == nullptr) {
        SDL_Log("Error loading restart.bmp2: %s", SDL_GetError());
        return;
    }
    tex2 = SDL_CreateTextureFromSurface(renderer, bmp2);
    if (tex2 == nullptr) {
        SDL_Log("Error creating texture: %s", SDL_GetError());
        return;
    }
    // START BUTTON
    bmp3 = SDL_LoadBMP("batdau.bmp");
    if (bmp3 == nullptr) {
        SDL_Log("Error loading restart.bmp2: %s", SDL_GetError());
        return;
    }
    tex3 = SDL_CreateTextureFromSurface(renderer, bmp3);
    if (tex3 == nullptr) {
        SDL_Log("Error creating texture: %s", SDL_GetError());
        return;
    }
    // ĐỒ HOẠ ĐẦU RẮN
    bmp4 = SDL_LoadBMP("head.bmp");
    if (bmp4 == nullptr) {
        SDL_Log("Error loading restart.bmp2: %s", SDL_GetError());
        return;
    }
    tex4 = SDL_CreateTextureFromSurface(renderer, bmp4);
    if (tex4 == nullptr) {
        SDL_Log("Error creating texture: %s", SDL_GetError());
        return;
    }
    // ĐỒ HOẠ THÂN RẮN
    bmp5 = SDL_LoadBMP("body.bmp");
    if (bmp5 == nullptr) {
        SDL_Log("Error loading restart.bmp2: %s", SDL_GetError());
        return;
    }
    tex5 = SDL_CreateTextureFromSurface(renderer, bmp5);
    if (tex5 == nullptr) {
        SDL_Log("Error creating texture: %s", SDL_GetError());
        return;
    }
    // ĐỒ HOẠ THỨC ĂN
    bmp6 = SDL_LoadBMP("food.bmp");
    if (bmp6 == nullptr) {
        SDL_Log("Error loading restart.bmp2: %s", SDL_GetError());
        return;
    }
    tex6 = SDL_CreateTextureFromSurface(renderer, bmp6);
    if (tex6 == nullptr) {
        SDL_Log("Error creating texture: %s", SDL_GetError());
        return;
    }
    // BACKGROUND TRƯỚC KHI BẤM START
    bmp7 = SDL_LoadBMP("backgroundbandau.bmp");
    if (bmp7 == nullptr) {
        SDL_Log("Error loading restart.bmp2: %s", SDL_GetError());
        return;
    }
    tex7 = SDL_CreateTextureFromSurface(renderer, bmp7);
    if (tex7 == nullptr) {
        SDL_Log("Error creating texture: %s", SDL_GetError());
        return;
    }
    // WALL
    bmp8 = SDL_LoadBMP("wall.bmp");
    if (bmp8 == nullptr) {
        SDL_Log("Error loading restart.bmp2: %s", SDL_GetError());
        return;
    }
    tex8 = SDL_CreateTextureFromSurface(renderer, bmp8);
    if (tex8 == nullptr) {
        SDL_Log("Error creating texture: %s", SDL_GetError());
        return;
    }
    // WALLCODINH
    bmp9 = SDL_LoadBMP("wallcodinh.bmp");
    if (bmp9 == nullptr) {
        SDL_Log("Error loading restart.bmp2: %s", SDL_GetError());
        return;
    }
    tex9 = SDL_CreateTextureFromSurface(renderer, bmp9);
    if (tex9 == nullptr) {
        SDL_Log("Error creating texture: %s", SDL_GetError());
        return;
    }
    // GAMEOVER
    bmp10 = SDL_LoadBMP("gameover.bmp");
    if (bmp10 == nullptr) {
        SDL_Log("Error loading restart.bmp2: %s", SDL_GetError());
        return;
    }
    tex10 = SDL_CreateTextureFromSurface(renderer, bmp10);
    if (tex10 == nullptr) {
        SDL_Log("Error creating texture: %s", SDL_GetError());
        return;
    }

    // Khởi tạo TTF
    if (!TTF_Init()) {
        SDL_Log("Can not down ttf:%s", SDL_GetError());
        return;
    }
    TTF_Font* font = TTF_OpenFont("font_pixel.ttf", 24);
    if (!font) {
        SDL_Log("Can not down font:%s", SDL_GetError());
        return;
    }
    SDL_Color textColor = { 255, 255, 255, 255 };

    // Khởi tạo điểm số
    std::string scoreText = "Your Score: " + std::to_string(score);
    scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(),
        strlen(scoreText.c_str()), textColor);
    scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);

    // Khởi tạo điểm cao nhất
    std::string highScoreText = "High Score: " + std::to_string(highScore);
    highScoreSurface = TTF_RenderText_Solid(
        font, highScoreText.c_str(), strlen(highScoreText.c_str()), textColor);
    highScoreTexture = SDL_CreateTextureFromSurface(renderer, highScoreSurface);

    // Khởi tạo level
    std::string LevelText = "Level : " + std::to_string(level);
    LevelSurface = TTF_RenderText_Solid(
        font, LevelText.c_str(), strlen(LevelText.c_str()), textColor);
    LevelTexture = SDL_CreateTextureFromSurface(renderer, LevelSurface);

    for (int i = length - 1; i >= 0; i--) {
        body.push_back({ 40, 40, GRID_SIZE, GRID_SIZE });
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
}

void cleanupResources() {
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
    SDL_DestroySurface(bmp9);
    SDL_DestroyTexture(tex9);
    SDL_DestroySurface(bmp10);
    SDL_DestroyTexture(tex10);
    SDL_DestroySurface(scoreSurface);
    SDL_DestroyTexture(scoreTexture);
    SDL_DestroySurface(highScoreSurface);
    SDL_DestroyTexture(highScoreTexture);
    SDL_DestroySurface(LevelSurface);
    SDL_DestroyTexture(LevelTexture);
    TTF_Quit();
    SDL_Quit();
}