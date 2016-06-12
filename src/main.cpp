#include <SDL/SDL.h>
#include "Window.h"
#include "Screen.h"
#include "Character.h"
#include "Grid.h"

int main(int argv, char** args)
{
    Screen& mainScreen = *(Window::newInstance(352, 352, "BomberMan", "icon.bmp").Getscreen());
    mainScreen.setBgColor(20, 20, 20);
    mainScreen.setFps(30);
    mainScreen.activateA_R(true);

    Grid gameGrid;
    Character bomberman(33, 33, {0, 18, 24, 32});
    gameGrid.getTile(1,1)->setBomber(&bomberman);

    mainScreen.activateA_R(false);
    Window::destroy();
    return 0;
}








