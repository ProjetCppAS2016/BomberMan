#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Window.h"
#include "IMGSurface.h"

using namespace std;

int main(int argv, char** args)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        fprintf(stderr, "Erreur dans l'initialisation de la SDL: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if (TTF_Init())
        fprintf(stderr, "Erreur dans l'initialisation de SDL_ttf: %s", TTF_GetError());

    Window main_w (400, 800, "BomberMan", "icon.bmp");
    main_w.getScreen().setBgColor(10, 190, 220);
    IMGSurface test("cutie.png");
    //test.setAlpha(true, 150);
    main_w.getScreen().addComponent(test);

    main_w.waitEvent(SDL_QUIT);

    TTF_Quit();
    SDL_Quit();
    return 0;
}
