#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Window.h"
#include "BMPSurface.h"

using namespace std;

int main(int argv, char** args)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        fprintf(stderr, "Erreur dans l'initialisation de la SDL: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    Window main_w (400, 800, "BomberMan", "icon.bmp");
    main_w.getScreen().setBgColor(10, 190, 220);
    BMPSurface test("cutie.bmp");
    main_w.getScreen().addComponent(test);

    main_w.WaitEvent(SDL_QUIT);

    SDL_Quit();
    return 0;
}
