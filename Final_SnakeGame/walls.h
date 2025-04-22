#pragma once
#ifndef WALLS_H
#define WALLS_H

#include <SDL3/SDL.h>
#include "game.h"

const int WALLSIZE = 7;
extern float wallx[];
extern float wally[];
extern float wallw[];
extern float wallh[];
extern Object wall;
extern int directionwall;
extern int nowtime;
extern SDL_FRect rw1, rw2, rw3, rw4, rw5, rw6, rw7;
extern SDL_FRect rectwall[];

int randomx();
int randomy();
void drawwall();
void drawwallDoNotRun();
void updateWall();

#endif