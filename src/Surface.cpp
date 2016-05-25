#include <SDL/SDL.h>
#include <iostream>
#include "Surface.h"

Surface::Surface() : surface(NULL), x(0), y(0), disp_w(-1), disp_h(-1)
{}
Surface::Surface(SDL_Surface* s) : surface(s), x(0), y(0), disp_w(-1), disp_h(-1)
{}
Surface::Surface(SDL_Surface* s, int x, int y) : surface(s), x(x), y(y), disp_w(-1)
{}
Surface::Surface(SDL_Surface* s, int x, int y, int w, int h) : surface(s), x(x), y(y), disp_w(w), disp_h(h)
{}

Surface::~Surface()
{ if (surface!=NULL) SDL_FreeSurface(surface); }

Surface::Surface(Surface const& other) : surface(NULL), x(other.x), y(other.y), disp_w(other.disp_w), disp_h(other.disp_h)
{
    if (other.surface!=NULL) *surface = *(other.surface);
}

Surface& Surface::operator=(const Surface& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    *surface = *(rhs.surface);
    x = rhs.x;
    y = rhs.y;
    disp_h = rhs.disp_h;
    disp_w = rhs.disp_w;

    return *this;
}

void Surface::setAlpha(bool active, int alpha)
{
    if (active)
        SDL_SetAlpha(surface, SDL_SRCALPHA, alpha);
    else
        SDL_SetAlpha(surface, 0, 0);
}













