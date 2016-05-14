#include <SDL/SDL.h>
#include "Surface.h"
#include "FlatSurface.h"

FlatSurface::FlatSurface() : Surface()
{ height = width = x = y = color = 0; }

FlatSurface::FlatSurface(Uint32 flag, int h, int w, int x2, int y2, Uint32 c) : Surface(SDL_CreateRGBSurface(flag, w, h, 32, 0, 0, 0, 0))
{
    height = h;
    width = w;
    x = x2;
    y = y2;
    color = c;
    SDL_FillRect(surface, NULL, color);
}

FlatSurface::FlatSurface(Uint32 flag, int h, int w, int x2, int y2, int r, int g, int b) : Surface(SDL_CreateRGBSurface(flag, w, h, 32, 0, 0, 0, 0))
{
    height = h;
    width = w;
    x = x2;
    y = y2;
    color = SDL_MapRGB(surface->format, r, g, b);
    SDL_FillRect(surface, NULL, color);
}

FlatSurface::~FlatSurface()
{ Surface::~Surface(); }

FlatSurface::FlatSurface(const FlatSurface& other) : height(other.height), width(other.width), color(other.color)
{ Surface::Surface(other); }





