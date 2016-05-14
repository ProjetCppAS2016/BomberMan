#include "Screen.h"
#include "Surface.h"

Screen::Screen() : Surface()
{}
Screen::Screen(SDL_Surface *s) : Surface(s)
{}

Screen::~Screen()
{}

Screen::Screen(const Screen& other) : Surface(other)
{}


void Screen::setBgColor(int r, int g, int b)
{
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, r, g, b));
    SDL_Flip(surface);
}

void Screen::refresh()
{ SDL_Flip(surface); }

void Screen::addComponent(Surface& component)
{
    SDL_Rect position;
    position.x = component.Getx();
    position.y = component.Gety();
    if (component.getDisp_h()!=-1)
        position.h = component.getDisp_h();
    if (component.getDisp_w()!=-1)
        position.w = component.getDisp_w();

    SDL_BlitSurface(component.getSurface(), NULL, surface, &position);
    refresh();
}







