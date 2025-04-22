#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <SDL3/SDL.h>

const int GRID_SIZE = 40;
const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 1000;

typedef struct {
    int x, y;
    int w, h;
} Object;

enum Direction { LEFT, RIGHT, UP, DOWN };

extern std::vector<Object> body;
extern Object Food;
extern int score;
extern int highScore;
extern int level;
extern int toadox, toadoy;
extern bool gameend;
extern bool start;
extern bool started;
extern bool vavaotuong;
extern bool mark;
extern bool click;
extern int countf;
extern int countf2;
extern int length;
extern Direction direction;
extern Direction pendingDirection;
extern Uint32 lastime;
extern Uint32 lastimeeatfood;
extern int timedelay;
extern int uplevel;
extern int consttime;
extern int increasetime;

void random2();
void touch();
void updateSnake();
void restartGameLogic();

#endif