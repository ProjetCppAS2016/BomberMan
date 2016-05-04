#include <SDL/SDL.h>
#include <iostream>
#include "Surface.h"

Surface::Surface() : surface(NULL)
{}
Surface::Surface(SDL_Surface* s) : surface(s)
{}

Surface::~Surface()
{}

Surface::Surface(const Surface& other)
{
    surface = other.surface;
}

SDL_Surface* Surface::getSurface() { return surface; }
