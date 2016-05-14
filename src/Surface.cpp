#include <SDL/SDL.h>
#include <iostream>
#include "Surface.h"

Surface::Surface() : surface(NULL), x(-1), y(-1), disp_w(-1), disp_h(-1)
{}
Surface::Surface(SDL_Surface* s) : surface(s), x(-1), y(-1), disp_w(-1), disp_h(-1)
{}
Surface::Surface(SDL_Surface* s, int x, int y) : surface(s), x(x), y(y), disp_w(-1), disp_h(-1)
{}
Surface::Surface(SDL_Surface* s, int x, int y, int w, int h) : surface(s), x(x), y(y), disp_w(w), disp_h(h)
{}

Surface::~Surface()
{ delete surface; }

Surface::Surface(const Surface& other) : x(other.x), y(other.y), disp_w(other.disp_w), disp_h(other.disp_h)
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






