#include <SDL/SDL.h>
#include <iostream>
#include "Surface.h"

Surface::Surface() : surface(NULL), disp_h(-1), disp_w(-1), x(-1), y(-1)
{}
Surface::Surface(SDL_Surface* s) : surface(s), disp_h(-1), disp_w(-1), x(-1), y(-1)
{}
Surface::Surface(SDL_Surface* s, int h, int w) : surface(s), disp_h(h), disp_w(w), x(-1), y(-1)
{}
Surface::Surface(SDL_Surface* s, int h, int w, int x, int y) : surface(s), disp_h(h), disp_w(w), x(x), y(y)
{}

Surface::~Surface()
{ delete surface; }

Surface::Surface(const Surface& other) : disp_h(other.disp_h), disp_w(other.disp_w), x(other.x), y(other.y)
{ *surface = *(other.surface); }

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






