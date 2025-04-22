#include "game.h"
#include "walls.h"
#include <cstdlib>

std::vector<Object> body;
Object Food;
int score = 0;
int highScore = 0;
int level = 1;
int toadox, toadoy;
bool gameend = false;
bool start = true;
bool started = false;
bool vavaotuong = false;
bool mark = false;
bool click = false;
int countf = 0;
int countf2 = 1;
int length = 3;
Direction direction = RIGHT;
Direction pendingDirection = RIGHT;
Uint32 lastime = 0;
Uint32 lastimeeatfood = 0;
int timedelay = consttime;
int uplevel = 4;
int consttime = 150;
int increasetime = 30;

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
    score += 10;
    if (score > highScore)
        highScore = score;
}

void updateSnake() {
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

        if (body[0].x)
            if (body[0].x == Food.x && body[0].y == Food.y) {
                touch();
                countf++;
                length++;
                countf2++;
                body.push_back(
                    { body[length - 2].x, body[length - 2].y, GRID_SIZE, GRID_SIZE });
            }
        for (int i = 1; i < length; i++) {
            if (body[i].x == Food.x && body[i].y == Food.y) {
                touch();
            }
        }
        if (countf == uplevel && timedelay >= 80) {
            timedelay -= increasetime;
            countf = 0;
            level += 1;
            uplevel += 3;
        }

        if ((currentime - lastimeeatfood >= 7000) && mark == true) {
            lastimeeatfood = currentime;

            for (int i = length - 1; i > 0; i--) {
                body[i] = body[i - 1];
            }
            if (direction == UP && body[0].y > 3 * GRID_SIZE) {
                body[0].y -= 3 * GRID_SIZE;
            }
            else if (direction == DOWN &&
                body[0].y < WINDOW_HEIGHT - 3 * GRID_SIZE) {
                body[0].y += 3 * GRID_SIZE;
            }
            else if (direction == RIGHT &&
                body[0].x < WINDOW_WIDTH - 2 * GRID_SIZE) {
                body[0].x += 3 * GRID_SIZE;
            }
            else if (direction == LEFT && body[0].x > 3 * GRID_SIZE) {
                body[0].x -= 3 * GRID_SIZE;
            }
            mark = false;
        }
        else if ((currentime - lastimeeatfood < 5000) && mark == true) {
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
                vavaotuong = true;
            }
        }
    }
}

void restartGameLogic() {
    Uint32 currentime = SDL_GetTicks();
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