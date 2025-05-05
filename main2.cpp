#include <SDL3/SDL.h>
#include "game.h"
#include "renderer.h"
#include "input.h"
#include "resources.h"
#include "walls.h"

int main(int argc, char* argv[]) { 
    initResources();
    wall.x = randomx();
    wall.y = randomy();
    if (wall.y == body[0].y) {
        wall.y = randomy();
    }
    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            handleInput(&event);
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
        if (!started) {
            renderStartScreen();
        }
        else {
            if (lv1)
            {
                updateSnake();
                updateWall();
                dandichuyen(); // Update bullet
                renderGame();
                So_Dan_Con_Lai();
            }

            if (click) {
                restartGameLogic();
            }
            next_Level();
            if (lv2)
            {
                updateWall();
                updateSnake();
                dandichuyen();
                renderGame();
                if (click) {
                    restartGameLogic();
                }
            }

        }
    }
    cleanupResources();
    return 0;
}
