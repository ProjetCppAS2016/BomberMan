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

BMPSurface::BMPSurface(string p, int h, int w) : Surface(NULL, h, w), path(p)
{ initBMP(); }

BMPSurface::BMPSurface(string p, int h, int w, int x, int y) : Surface(NULL, h, w, x, y), path(p)
{ initBMP(); }

BMPSurface::~BMPSurface()
{ Surface::~Surface(); }

BMPSurface::BMPSurface(const BMPSurface& other) : path(other.path)
{ Surface::Surface(other); }


BMPSurface::setTransparency()
{

}








