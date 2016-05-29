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

using namespace std;

string intToStr(int i)
{
    std::ostringstream stream;
    stream << i;
    return stream.str();
}

int main(int argv, char** args)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        fprintf(stderr, "Erreur dans l'initialisation de la SDL: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if (TTF_Init())
        fprintf(stderr, "Erreur dans l'initialisation de SDL_ttf: %s", TTF_GetError());

    Screen& mainScreen = Window::newInstance(352, 352, "BomberMan", "icon.bmp").getScreen();
    mainScreen.setBgColor(20, 20, 20);

    TILE* grid[GRID_SIZE][GRID_SIZE];
    for (int x=0; x<GRID_SIZE; x++) {
        for (int y=0; y<GRID_SIZE; y++) {
            grid[x][y] = new TILE;
            grid[x][y]->contain = NTHG;
            grid[x][y]->xMin = x*32;
            grid[x][y]->xMax = x*32+32;
            grid[x][y]->yMin = y*32;
            grid[x][y]->yMax = y*32+32;
        }
    }
    for (int i=0; i<GRID_SIZE; i++) {
        grid[0][i]->contain = WALL;
        grid[GRID_SIZE-1][i]->contain = WALL;
        grid[i][0]->contain = WALL;
        grid[i][GRID_SIZE-1]->contain = WALL;
    }
    for (int x=2; x<GRID_SIZE-2; x+=2)
        for (int y=2; y<GRID_SIZE-2; y+=2)
            grid[x][y]->contain = WALL;

    string imgPath;
    for (int x=0; x<GRID_SIZE; x++) {
        for (int y=0; y<GRID_SIZE; y++) {
            switch (grid[x][y]->contain)
            {
            case WALL:
                imgPath = "textures\\wall.bmp";
                break;

            case NTHG:
                imgPath = "textures\\floor.bmp";
                break;
            }
            mainScreen.addStaticComponent(new BMPSurface(imgPath, grid[x][y]->xMin, grid[x][y]->yMin), false);
        }
    }
    mainScreen.clearScreen();

    Sprite spLeft(1, 120, NULL), spRight(1, 120, NULL), spUp(1, 120, NULL), spDown(1, 120, NULL);
    string L("textures\\left_"), pathLeft, R("textures\\right_"), pathRight,
           U("textures\\up_"), pathUp, D("textures\\down_"), pathDown, bmp(".bmp");
    BMPSurface *tmp;
    for (int i=1; i<7; i++) {
        pathLeft = L + intToStr(i) + bmp;
        pathRight = R + intToStr(i) + bmp;
        pathUp = U + intToStr(i) + bmp;
        pathDown = D + intToStr(i) + bmp;
        tmp = new BMPSurface(pathLeft);
        tmp->setTransparency(true, 0, 255, 0);
        spLeft.addImg(tmp);
        tmp = new BMPSurface(pathRight);
        tmp->setTransparency(true, 0, 255, 0);
        spRight.addImg(tmp);
        tmp = new BMPSurface(pathUp);
        tmp->setTransparency(true, 0, 255, 0);
        spUp.addImg(tmp);
        tmp = new BMPSurface(pathDown);
        tmp->setTransparency(true, 0, 255, 0);
        spDown.addImg(tmp);
    }
    mainScreen.addComponent(&spLeft, false);
    mainScreen.addComponent(&spRight, false);
    mainScreen.addComponent(&spUp, false);
    mainScreen.addComponent(&spDown, true);

    mainScreen.activateA_R(true);

    Character bomberman(1, 1, 32, 32, &spLeft, &spRight, &spUp, &spDown, grid);
    bomberman.useSprite(RIGHT, 6);
    for (int i=0; i<30; i++) {
        bomberman.moveTo(DOWN);
        mainScreen.synchronise(20);
    }
    for (int i=0; i<30; i++) {
        bomberman.moveTo(RIGHT);
        mainScreen.synchronise(20);
    }

    Window::waitEvent(SDL_QUIT);

    mainScreen.activateA_R(false);
    Window::destroy();
    TTF_Quit();

    return 0;
}








