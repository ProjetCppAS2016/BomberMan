#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <vector>
#include "Window.h"
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

    Window main_w (400, 800, "BomberMan", "icon.bmp");
    main_w.getScreen().setBgColor(10, 10, 10);
    IMGSurface *cutie = new IMGSurface("cutie.png");
    main_w.getScreen().addStaticComponent(*cutie);

    Text txt_test1("Rainbow Dash!", "PonyRides.ttf", 60);
    txt_test1.setDefault_color(220, 220, 220);
    txt_test1.setDefault_type("blended");
    txt_test1.render();

    Text txt_test2("Rainbow Dash!", "PonyRides.ttf", 70);
    txt_test2.setDefault_color(220, 220, 220);
    txt_test2.setDefault_type("blended");
    txt_test2.render();

    Sprite test_spt(2, 1000, &txt_test1, &txt_test2);
    test_spt.Setx((400-test_spt.getSurface()->w) / 2);
    main_w.getScreen().addComponent(test_spt);
    main_w.getScreen().setFps(35);

    main_w.getScreen().activateA_R(true);

    test_spt.displaySprite(true);

    SDL_Delay(2000);
    for (int i=0; i<100; i++) {
        test_spt.Sety(test_spt.Gety()+1);
        Screen::synchronise(40);
    }

    test_spt.displaySprite(false);

    main_w.getScreen().activateA_R(false);

    txt_test1.close_font();
    txt_test2.close_font();
    main_w.waitEvent(SDL_QUIT);

    TTF_Quit();
    SDL_Quit();
    return 0;
}








