#include "Surface.h"
#include "BMPSurface.h"
#include "SDL/SDL.h"

using namespace std;

BMPSurface::BMPSurface() : Surface()
{}

void BMPSurface::initBMP()
{
    if ((surface = SDL_LoadBMP(path.c_str()))==NULL)
        fprintf(stderr, "Erreur dans le chargement de la BMP: %s", SDL_GetError());
}

BMPSurface::BMPSurface(string p) : Surface(), path(p)
{ initBMP(); }

BMPSurface::BMPSurface(string p, int x, int y) : Surface(NULL, x, y), path(p)
{ initBMP(); }

BMPSurface::BMPSurface(string p, int x, int y, int h, int w) : Surface(NULL, x, y, h, w), path(p)
{ initBMP(); }

BMPSurface::~BMPSurface()
{}

BMPSurface::BMPSurface(const BMPSurface& other) : Surface(other), path(other.path)
{}


void BMPSurface::setTransparency(bool active, Uint32 t_color)
{
    if (active)
        SDL_SetColorKey(surface, SDL_SRCCOLORKEY, t_color);
    else
        SDL_SetColorKey(surface, 0, 0);
}

void BMPSurface::setTransparency(bool active, int r, int g, int b)
{
    if (active)
        SDL_SetColorKey(surface, SDL_SRCCOLORKEY, SDL_MapRGB(surface->format, r, g, b));
    else
        SDL_SetColorKey(surface, 0, 0);
}








