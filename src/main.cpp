#include <SDL/SDL.h>
#include "Window.h"
#include "Screen.h"
#include "Bomberman.h"
#include "Grid.h"

int main(int argv, char** args)
{
    Screen& mainScreen = *(Window::newInstance(352, 352, "BomberMan", "icon.bmp").Getscreen());
    mainScreen.setBgColor(20, 20, 20);
    mainScreen.setFps(30);
    mainScreen.activateA_R(true);

    Grid gameGrid;
    Bomberman bomber(33, 33, {0, 18, 24, 32}, &gameGrid);
    gameGrid.getTile(1,1)->setBomber(&bomber);
    bomber.waitEvents();

    mainScreen.activateA_R(false);
    Window::destroy();
    return 0;
}








