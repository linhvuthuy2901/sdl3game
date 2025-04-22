#include "renderer.h"
#include "game.h"
#include "walls.h"

SDL_Renderer* renderer = nullptr;
SDL_Texture* tex = nullptr;
SDL_Surface* bmp = nullptr;
SDL_Texture* tex2 = nullptr;
SDL_Surface* bmp2 = nullptr;
SDL_Texture* tex3 = nullptr;
SDL_Surface* bmp3 = nullptr;
SDL_Texture* tex4 = nullptr;
SDL_Surface* bmp4 = nullptr;
SDL_Texture* tex5 = nullptr;
SDL_Surface* bmp5 = nullptr;
SDL_Texture* tex6 = nullptr;
SDL_Surface* bmp6 = nullptr;
SDL_Texture* tex7 = nullptr;
SDL_Surface* bmp7 = nullptr;
SDL_Texture* tex8 = nullptr;
SDL_Surface* bmp8 = nullptr;
SDL_Texture* tex9 = nullptr;
SDL_Surface* bmp9 = nullptr;
SDL_Texture* tex10 = nullptr;
SDL_Surface* bmp10 = nullptr;
SDL_Surface* scoreSurface = nullptr;
SDL_Texture* scoreTexture = nullptr;
SDL_Surface* highScoreSurface = nullptr;
SDL_Texture* highScoreTexture = nullptr;
SDL_Surface* LevelSurface = nullptr;
SDL_Texture* LevelTexture = nullptr;
SDL_FRect destRect = { 310.0f, 450.0f, 370.0f, 300.0f };
SDL_FRect srcRect = { 0.0f, 0.0f, 0.0f, 0.0f };
SDL_FRect destRect2 = { 400.0f, 300.0f, 200.0f, 100.0f };
SDL_FRect destRect3 = { 240.0f, -20.0f, 500.0f, 400.0f };

void food() {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_FRect rect3 = { (float)Food.x, (float)Food.y, (float)GRID_SIZE,
                       (float)GRID_SIZE };
    SDL_RenderTexture(renderer, tex6, NULL, &rect3);
}

void renderSnake() {
    for (int i = length - 1; i >= 0; i--) {
        SDL_FRect rect1 = { (float)body[i].x, (float)body[i].y, (float)body[i].w,
                           (float)body[i].h };
        if (i == 0) {
            SDL_RenderTexture(renderer, tex4, NULL, &rect1);
        }
        else {
            SDL_RenderTexture(renderer, tex5, NULL, &rect1);
        }
    }
}

void renderScore() {
    TTF_Font* font = TTF_OpenFont("font_pixel.ttf", 24);
    SDL_Color textColor = { 255, 255, 255, 255 };
    std::string scoreText = "Your Score: " + std::to_string(score);
    if (scoreSurface)
        SDL_DestroySurface(scoreSurface);
    if (scoreTexture)
        SDL_DestroyTexture(scoreTexture);
    scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(),
        strlen(scoreText.c_str()), textColor);
    scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_FRect scoreRect = { 90.0f, 70.0f, 200.0f, 30.0f };
    SDL_RenderTexture(renderer, scoreTexture, NULL, &scoreRect);
    TTF_CloseFont(font);
}

void renderHighScore() {
    TTF_Font* font = TTF_OpenFont("font_pixel.ttf", 24);
    SDL_Color textColor = { 255, 255, 255, 255 };
    std::string highScoreText = "High Score: " + std::to_string(highScore);
    if (highScoreSurface)
        SDL_DestroySurface(highScoreSurface);
    if (highScoreTexture)
        SDL_DestroyTexture(highScoreTexture);
    highScoreSurface = TTF_RenderText_Solid(
        font, highScoreText.c_str(), strlen(highScoreText.c_str()), textColor);
    highScoreTexture = SDL_CreateTextureFromSurface(renderer, highScoreSurface);
    SDL_FRect highScoreRect = { 90.0f, 100.0f, 200.0f, 30.0f };
    SDL_RenderTexture(renderer, highScoreTexture, NULL, &highScoreRect);
    TTF_CloseFont(font);
}

void renderLevel() {
    TTF_Font* font = TTF_OpenFont("font_pixel.ttf", 24);
    SDL_Color textColor = { 255, 255, 255, 255 };
    std::string LevelText = "Level : " + std::to_string(level);
    if (LevelSurface)
        SDL_DestroySurface(LevelSurface);
    if (LevelTexture)
        SDL_DestroyTexture(LevelTexture);
    LevelSurface = TTF_RenderText_Solid(
        font, LevelText.c_str(), strlen(LevelText.c_str()), textColor);
    LevelTexture = SDL_CreateTextureFromSurface(renderer, LevelSurface);
    SDL_FRect LevelRect = { 90.0f, 40.0f, 140.0f, 30.0f };
    SDL_RenderTexture(renderer, LevelTexture, NULL, &LevelRect);
    TTF_CloseFont(font);
}

void renderStartScreen() {
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, tex7, NULL, NULL);
    SDL_RenderTexture(renderer, tex3, &srcRect, &destRect);
    SDL_RenderPresent(renderer);
}

void restartGame() {
    if (tex) {
        SDL_RenderTexture(renderer, tex, &srcRect, &destRect2);
        SDL_Log("Rendering restart texture at %.0f, %.0f", destRect2.x,
            destRect2.y);
    }
    else {
        SDL_Log("Texture is null!");
    }
    SDL_RenderPresent(renderer);
}

void renderGame() {
    SDL_RenderClear(renderer);

    if (gameend == true) {
        SDL_RenderTexture(renderer, tex2, NULL, NULL);
        SDL_RenderTexture(renderer, tex10, &srcRect, &destRect3); // gameover.bmp
        renderScore();
        renderHighScore();
        renderLevel();
        SDL_RenderTexture(renderer, tex, &srcRect, &destRect2); // restart.bmp
    }
    else {
        SDL_RenderTexture(renderer, tex2, NULL, NULL); // background
        if (vavaotuong == false) {
            drawwallDoNotRun(); // Tường cố định
        }
        renderScore();
        renderHighScore();
        renderLevel();
        food(); // Thức ăn
        for (int i = 0; i < WALLSIZE; i++) {
            if (Food.x >= wallx[i] && Food.y >= wally[i] &&
                Food.x <= wallx[i] + wallw[i] && Food.y <= wally[i] + wallh[i]) {
                Food.x = randomx();
                Food.y = randomy();
            }
        }
        renderSnake(); // Rắn
        drawwall(); // Tường di động
    }

    SDL_RenderPresent(renderer);
}