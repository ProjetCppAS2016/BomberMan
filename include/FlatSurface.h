#ifndef FLATSURFACE_H
#define FLATSURFACE_H

#include "Surface.h"
#include <SDL/SDL.h>


class FlatSurface : public Surface
{
    public:
        FlatSurface();
        FlatSurface(Uint32, int, int, int, int, Uint32);
        FlatSurface(Uint32, int, int, int, int, int, int, int);
        ~FlatSurface();
        FlatSurface(const FlatSurface& other);

        int Getheight() { return height; }
        void Setheight(int val) { height = val; }
        int Getwidth() { return width; }
        void Setwidth(int val) { width = val; }
        Uint32 getColor() { return color; }
        void setColor(int, int, int);

    protected:

    private:
        int height;
        int width;
        Uint32 color;
};

#endif // FLATSURFACE_H
