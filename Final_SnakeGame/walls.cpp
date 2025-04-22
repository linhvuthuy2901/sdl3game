#include "walls.h"
#include "game.h"
#include "renderer.h"

float wallx[] = { GRID_SIZE * 8,  GRID_SIZE * 7, GRID_SIZE * 2, GRID_SIZE * 18,
                 GRID_SIZE * 16, GRID_SIZE * 3, GRID_SIZE * 16 };
float wally[] = { GRID_SIZE * 13, GRID_SIZE * 7,  GRID_SIZE * 4, GRID_SIZE * 2,
                 GRID_SIZE * 8,  GRID_SIZE * 11, GRID_SIZE * 16 };
float wallw[] = { GRID_SIZE * 1, GRID_SIZE * 10, GRID_SIZE * 1, GRID_SIZE,
                 GRID_SIZE,     GRID_SIZE * 11, GRID_SIZE * 7 };
float wallh[] = { GRID_SIZE * 5, GRID_SIZE, GRID_SIZE * 4, GRID_SIZE * 8,
                 GRID_SIZE * 7, GRID_SIZE, GRID_SIZE };
Object wall;
int directionwall = false;
int nowtime = 0;
SDL_FRect rw1, rw2, rw3, rw4, rw5, rw6, rw7;
SDL_FRect rectwall[] = { rw1, rw2, rw3, rw4, rw5, rw6, rw7 };

int randomx() { return (rand() % (WINDOW_WIDTH / GRID_SIZE)) * GRID_SIZE; }
int randomy() { return (rand() % (WINDOW_HEIGHT / GRID_SIZE)) * GRID_SIZE; }

void drawwall() {
    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);
    SDL_FRect rect3 = { (float)wall.x, (float)wall.y, (float)GRID_SIZE,
                       (float)GRID_SIZE };
    SDL_RenderTexture(renderer, tex8, NULL, &rect3);
}

void drawwallDoNotRun() {
    for (int i = 0; i < WALLSIZE; i++) {
        rectwall[i] = { wallx[i], wally[i], wallw[i], wallh[i] };
        SDL_RenderTexture(renderer, tex9, NULL, &rectwall[i]);
    }
}

void updateWall() {
    Uint32 currentime = SDL_GetTicks();
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
    if (countf2 % 4 == 0) {
        wall.x = randomx();
        wall.y = randomy();
        if ((wall.x == body[0].x || wall.y == body[0].y)) {
            wall.x = randomx();
            wall.y = randomy();
        }
        countf2 = 1;
    }
    for (int i = 0; i < WALLSIZE; i++) {
        if (body[0].x >= wallx[i] && body[0].x < wallx[i] + wallw[i] &&
            body[0].y >= wally[i] && body[0].y < wally[i] + wallh[i]) {
            gameend = true;
            vavaotuong = true;
        }
    }
    if (body[0].x == wall.x && body[0].y == wall.y) {
        gameend = true;
        vavaotuong = true;
    }
}