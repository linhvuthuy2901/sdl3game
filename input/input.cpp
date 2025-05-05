#include "input.h"
#include "game.h"
#include "renderer.h"

#include "input.h"
#include "game.h"
#include "renderer.h"

void handleInput(SDL_Event* event) {
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
        case SDL_SCANCODE_SPACE: {
            if (!bullet && bulletCount > 0) {
                bullet = true;
                Dan.x = body[0].x;
                Dan.y = body[0].y;
                lasttimebullet = SDL_GetTicks();
                bulletCount--;
                foodSinceLastBullet = 0; //  Reset đếm food sau khi sử dụng đạn
            }
            break;
        }
        default: {
            break;
        }
        }
    }

    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN && gameend) {
        int mouseX = event->button.x;
        int mouseY = event->button.y;
        if (mouseX >= destRect2.x && mouseX <= destRect2.x + destRect2.w &&
            mouseY >= destRect2.y && mouseY <= destRect2.y + destRect2.h) {
            click = true;
            SDL_Log("Click to continue %d, %d", mouseX, mouseY);
        }
    }

    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN && start) {
        int mouseX = event->button.x;
        int mouseY = event->button.y;
        if (mouseX >= destRect.x && mouseX <= destRect.x + destRect.w &&
            mouseY >= destRect.y && mouseY <= destRect.y + destRect.h) {
            start = false;
            started = true;
            SDL_Log("Click to continue %d, %d", mouseX, mouseY);
        }
    }
}
