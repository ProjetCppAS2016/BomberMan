#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <vector>
#include "Window.h"
#include "Screen.h"
#include "IMGSurface.h"
#include "Text.h"
#include "Sprite.h"

using namespace std;

int main(int argv, char** args)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        fprintf(stderr, "Erreur dans l'initialisation de la SDL: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if (TTF_Init())
        fprintf(stderr, "Erreur dans l'initialisation de SDL_ttf: %s", TTF_GetError());

    Screen& mainScreen = Window::newInstance(400, 800, "BomberMan", "icon.bmp").getScreen();
    mainScreen.setBgColor(20, 20, 20);



    Window::waitEvent(SDL_QUIT);

    Window::destroy();
    TTF_Quit();
    SDL_Quit();
    return 0;
}








