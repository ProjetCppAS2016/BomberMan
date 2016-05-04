#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Window.h"

using namespace std;

int main(int argv, char** args)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        cout << "Erreur dans l'initialisation de la SDL";
        exit(EXIT_FAILURE);
    }

    Window main_w (400, 400, 32);
    main_w.setBgColor(10, 190, 220);
    main_w.WaitEvent(SDL_QUIT);

    SDL_Quit();
    return 0;
}
