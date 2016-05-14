#ifndef SURFACE_H
#define SURFACE_H
#include <SDL/SDL.h>
#include <iostream>


class Surface
{
    public:
        Surface();
        Surface(SDL_Surface*);
        Surface(SDL_Surface*, int, int);
        Surface(SDL_Surface*, int, int, int, int);
        virtual ~Surface();

        Surface(const Surface& other);
        Surface& operator=(const Surface&);
        SDL_Surface* getSurface() { return surface; }
        int getDisp_h() { return disp_h; }
        void setDisp_h(int h) { disp_h = h; }
        int getDisp_w() { return disp_w; }
        void setDisp_w(int w) { disp_w = w; }
        int Getx() { return x; }
        void Setx(int val) { x = val; }
        int Gety() { return y; }
        void Sety(int val) { y = val; }

    protected:
        SDL_Surface *surface;
        int x;
        int y;
        int disp_h;
        int disp_w;

    private:
};

#endif // SURFACE_H
