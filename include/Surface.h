#ifndef SURFACE_H
#define SURFACE_H
#include <SDL/SDL.h>
#include <iostream>


class Surface
{
    public:
        Surface();
        Surface(SDL_Surface*);
        virtual ~Surface();
        Surface(const Surface& other);
        SDL_Surface* getSurface();

    protected:

    private:
        SDL_Surface *surface;
};

#endif // SURFACE_H
