#include "IMGSurface.h"

using namespace std;

IMGSurface::IMGSurface() : Surface()
{}

void IMGSurface::initIMG()
{
    if ((surface = IMG_Load(path.c_str()))==NULL)
        fprintf(stderr, "Erreur dans le chargement de l'image: %s", IMG_GetError());
}

IMGSurface::IMGSurface(string p) : Surface(), path(p)
{ initIMG(); }

IMGSurface::IMGSurface(string p, int x, int y) : Surface(NULL, x, y), path(p)
{ initIMG(); }

IMGSurface::IMGSurface(string p, int x, int y, int h, int w) : Surface(NULL, x, y, h, w), path(p)
{ initIMG(); }

IMGSurface::~IMGSurface()
{}

IMGSurface::IMGSurface(const IMGSurface& other) : Surface(other), path(other.path)
{}

void IMGSurface::setImg(string p)
{
    path = p;
    initIMG();
}






