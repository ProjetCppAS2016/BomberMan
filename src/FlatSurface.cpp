#include <SDL/SDL.h>
#include "Surface.h"
#include "FlatSurface.h"

FlatSurface::FlatSurface() : Surface()
{ height = width = x = y = color = 0; }

FlatSurface::FlatSurface(Uint32 flag, int x, int y, int w, int h, Uint32 c) : Surface(SDL_CreateRGBSurface(flag, w, h, 32, 0, 0, 0, 0))
{
    height = h;
    width = w;
    this->x = x;
    this->y = y;
    color = c;
    SDL_FillRect(surface, NULL, color);
}

FlatSurface::FlatSurface(Uint32 flag, int x, int y, int w, int h, int r, int g, int b) : Surface(SDL_CreateRGBSurface(flag, w, h, 32, 0, 0, 0, 0))
{
    height = h;
    width = w;
    this->x = x;
    this->y = y;
    color = SDL_MapRGB(surface->format, r, g, b);
    SDL_FillRect(surface, NULL, color);
}

FlatSurface::~FlatSurface()
{}

FlatSurface::FlatSurface(const FlatSurface& other) : Surface(other), height(other.height), width(other.width), color(other.color)
{}

void FlatSurface::setColor(int r, int g, int b)
{
    color = SDL_MapRGB(surface->format, r, g, b);
    SDL_FillRect(surface, NULL, color);
    setModified(true);
}





