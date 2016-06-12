#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <vector>
#include <sstream>
#include "Window.h"
#include "Screen.h"
#include "IMGSurface.h"
#include "Text.h"
#include "Sprite.h"
#include "Character.h"
#include "Bomb.h"

using namespace std;

string intToStr(int i)
{
    std::ostringstream stream;
    stream << i;
    return stream.str();
}

int main(int argv, char** args)
{
    Screen& mainScreen = *(Window::newInstance(352, 352, "BomberMan", "icon.bmp").getScreen());
    mainScreen.setBgColor(20, 20, 20);

    mainScreen.setFps(30);

    mainScreen.activateA_R(true);

    HITBOX htb = {1, 17, 25, 31};
    Character bomberman(1, 1, htb, &spLeft, &spRight, &spUp, &spDown, grid);
    grid[1][1]->player = &bomberman;
    bomberman.useSprite(DOWN, 1);

    SDL_EnableKeyRepeat(5, 5);
    SDL_Event event;
    bool flag = true;

    while (flag) {
        SDL_WaitEvent(&event);

        if (!bomberman.isAlive()) {
            flag = false;
            bomberman.kill();
        } else {
            switch (event.type) {
            case SDL_QUIT:
                    flag = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                        bomberman.moveTo(LEFT);
                        mainScreen.synchronise(10);
                    break;
                case SDLK_RIGHT:
                        bomberman.moveTo(RIGHT);
                        mainScreen.synchronise(10);
                    break;
                case SDLK_UP:
                        bomberman.moveTo(UP);
                        mainScreen.synchronise(10);
                    break;
                case SDLK_DOWN:
                        bomberman.moveTo(DOWN);
                        mainScreen.synchronise(10);
                    break;
                case SDLK_SPACE:
                        bomberman.dropBomb();
                default:
                    break;
                }
                break;
            case SDL_KEYUP:
                bomberman.moveTo(STOP);
            }
        }
    }

    mainScreen.activateA_R(false);
    Window::destroy();
    return 0;
}








