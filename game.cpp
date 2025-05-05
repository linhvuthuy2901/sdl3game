#include "game.h"
#include "walls.h"
#include "renderer.h"
#include <SDL3/SDL.h>
#include <cstdlib>

std::vector<Object> body;
Object Food;
Object Dan;
int score = 0;
int highScore = 0;
int level = 1;
int toadox, toadoy;
int trudiem = 15;
bool gameend = false;
bool start = true;
bool started = false;
bool vavaotuong = false;
bool mark = false;
bool click = false;
bool bullet = false;
bool quanlihuongtrai = false;
bool quanlihuongphai = false;
bool quanlihuongtren = false;
bool quanlihuongduoi = false;
bool isPaused = false;
bool lv1 = true;
bool lv2 = false;
Uint32 lasttimebullet = 0;
int countf = 0;
int countf2 = 1;
int length = 3;
int foodCount = 1; 
int foodSinceLastBullet = 0; 
bool showGift = false;
Uint32 giftStartTime = 0;
Object Gift; 
bool giftEaten = false;
Object wall;

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
            i = -1; 
        }
    }
}

void touch() {
    random2();
    foodCount = 1; 
    score += 1;
    if (score > highScore)
        highScore = score;

    foodSinceLastBullet++; 

    if (foodSinceLastBullet >= 3) { 
        if (bulletCount < 3) {
            bulletCount++;
        }
        foodSinceLastBullet = 0; 
    }
    if (countf > 0 && countf % 5 == 0 && !showGift) {
        Gift.x = randomx();
        Gift.y = randomy();
        showGift = true;
        giftStartTime = SDL_GetTicks();
        giftEaten = false;
        for (int i = 0; i < WALLSIZE; i++)
        {
            if (Gift.x>=wallx[i] &&Gift.x<=wallx[i]+wallw[i] && Gift.y>= wally[i]&&Gift.y<=wally[i]+wallh[i])
            {
                Gift.x = randomx();
                Gift.y = randomy();

            }
        }
        if (Gift.x == Food.x && Gift.y == Food.y)
        {
            Gift.x = randomx();
            Gift.y = randomy();
        }
    }
    
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
            trudiem += 2;
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
        if (score <= -100)
        {
            gameend = true;
        }

    }
    if (showGift && !giftEaten &&
        body[0].x == Gift.x && body[0].y == Gift.y) {
        int points[] = { 5, 10, 15, 20, 25, 30, -5, -10,-20 };
        int n = sizeof(points) / sizeof(points[0]);
        int delta = points[rand() % n];
        score += delta;
        if (score > highScore) highScore = score;

        giftEaten = true;
        showGift = false; // Ẩn hộp quà sau khi ăn
    }
    if (showGift && SDL_GetTicks() - giftStartTime > 10000) {
        showGift = false;
        giftEaten = false;
    }

}

void restartGameLogic() {
    Uint32 currentime = SDL_GetTicks();
    timedelay = consttime;
    body.erase(body.begin() + 3, body.end());
    if (body.size() < 3) {
        body.resize(3); // Resize body nếu ít hơn 3 phần tử
    }
    length = 3;
    for (int i = 0; i < 3; i++) {
        body[i].x = GRID_SIZE;
        body[i].y = GRID_SIZE;
    }
    wall.x = randomx();
    wall.y = randomy();
    if (wall.y == 280 || wall.y == 40) {
        wall.y = randomy();
    }
    lastimeeatfood = currentime;
    direction = RIGHT;
    pendingDirection = RIGHT;
    countf = 0;
    countf2 = 1;
    foodCount = 1;
    gameend = false;
    click = false;
    random2();
    vavaotuong = false;
    score = 0;
    uplevel = 6;
    level = 1;
    bullet = false;
    Dan = { 0, 0, GRID_SIZE , GRID_SIZE };
    bulletCount = 3;
    foodSinceLastBullet = 0; // Reset đếm thức ăn
    showGift = false;
    giftEaten = false;
    giftStartTime = 0;

}


void dandichuyen() {
    int speed = GRID_SIZE /2;
    if (!bullet) {
        quanlihuongtren = false;
        quanlihuongduoi = false;
        quanlihuongtrai = false;
        quanlihuongphai = false;
        return;
    }

    if (direction == UP && !quanlihuongduoi && !quanlihuongphai && !quanlihuongtrai) {
        Dan.y -= speed;
        quanlihuongtren = true;
    }
    else if (direction == DOWN && !quanlihuongtren && !quanlihuongphai && !quanlihuongtrai) {
        Dan.y += speed;
        quanlihuongduoi = true;
    }
    else if (direction == LEFT && !quanlihuongtren && !quanlihuongphai && !quanlihuongduoi) {
        Dan.x -= speed;
        quanlihuongtrai = true;
    }
    else if (direction == RIGHT && !quanlihuongtren && !quanlihuongtrai && !quanlihuongduoi) {
        Dan.x += speed;
        quanlihuongphai = true;
    }

    if (Dan.x == Food.x && Dan.y == Food.y) {
        Food.x = randomx();
        Food.y = randomy();
        if (!body.empty()) {
            body.push_back({ body.back().x, body.back().y, GRID_SIZE, GRID_SIZE });
            length++;
        }
        touch();
        countf++;
        countf2++;
        touch();
        score += 9;
        bullet = false;
        foodCount = 1; // bắn trúng thì random mới
        quanlihuongtren = quanlihuongduoi = quanlihuongtrai = quanlihuongphai = false;
        return;
    }

    if (Dan.x < 0 || Dan.x >= WINDOW_WIDTH || Dan.y < 0 || Dan.y >= WINDOW_HEIGHT) {
        bullet = false;
        score -= trudiem;
        quanlihuongtren = quanlihuongduoi = quanlihuongtrai = quanlihuongphai = false;
        return;
    }

    for (int i = 0; i < WALLSIZE; i++) {
        if (Dan.x >= wallx[i] && Dan.x < wallx[i] + wallw[i] &&
            Dan.y >= wally[i] && Dan.y < wally[i] + wallh[i]) {
            bullet = false;
            quanlihuongtren = quanlihuongduoi = quanlihuongtrai = quanlihuongphai = false;
            return;
        }
    }
}

void drawbullet() {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_FRect rect4 = { (float)Dan.x, (float)Dan.y, (float)GRID_SIZE , (float)GRID_SIZE };
    SDL_RenderTexture(renderer, tex11, NULL, &rect4);
}
void renderGiftBox() {
    if (showGift && !giftEaten) {
        SDL_FRect rect = { (float)Gift.x, (float)Gift.y, (float)GRID_SIZE, (float)GRID_SIZE };
        SDL_RenderTexture(renderer, tex12, NULL, &rect); 
    }
}

