#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Window.h"
#include "IMGSurface.h"
#include "Text.h"

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
    main_w.getScreen().setBgColor(10, 10, 10);
    IMGSurface test("cutie.png");
    main_w.getScreen().addStaticComponent(test);

    Text txt_test("Rainbow Dash!", "PonyRides.ttf", 60);
    txt_test.setDefault_color(220, 220, 220);
    txt_test.setDefault_type("blended");
    txt_test.render();
    main_w.getScreen().addComponent(txt_test);

    txt_test.Setx((400-txt_test.getSurface()->w) / 2);
    /*main_w.getScreen().setAuto_refresh(true);

    SDL_Delay(5000);

    main_w.getScreen().setAuto_refresh(false);*/
main_w.getScreen().refresh();
main_w.getScreen().refresh();
    txt_test.close_font();

    main_w.waitEvent(SDL_QUIT);

    TTF_Quit();
    SDL_Quit();
    return 0;
}








