#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

extern SDL_Renderer* renderer;
extern SDL_Texture* tex;
extern SDL_Surface* bmp;
extern SDL_Texture* tex2;
extern SDL_Surface* bmp2;
extern SDL_Texture* tex3;
extern SDL_Surface* bmp3;
extern SDL_Texture* tex4;
extern SDL_Surface* bmp4;
extern SDL_Texture* tex5;
extern SDL_Surface* bmp5;
extern SDL_Texture* tex6;
extern SDL_Surface* bmp6;
extern SDL_Texture* tex7;
extern SDL_Surface* bmp7;
extern SDL_Texture* tex8;
extern SDL_Surface* bmp8;
extern SDL_Texture* tex9;
extern SDL_Surface* bmp9;
extern SDL_Texture* tex10;
extern SDL_Surface* bmp10;
extern SDL_Surface* scoreSurface;
extern SDL_Texture* scoreTexture;
extern SDL_Surface* highScoreSurface;
extern SDL_Texture* highScoreTexture;
extern SDL_Surface* LevelSurface;
extern SDL_Texture* LevelTexture;
extern SDL_FRect destRect;
extern SDL_FRect srcRect;
extern SDL_FRect destRect2;
extern SDL_FRect destRect3;

void food();
void renderSnake();
void renderScore();
void renderHighScore();
void renderLevel();
void renderStartScreen();
void restartGame();
void renderGame();

#endif