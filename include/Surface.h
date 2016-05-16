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
        void setSurface(SDL_Surface* s) { surface = s; }
        int getDisp_h() { return disp_h; }
        void setDisp_h(int h) { disp_h = h; setModified(true); }
        int getDisp_w() { return disp_w; }
        void setDisp_w(int w) { disp_w = w; setModified(true); }
        int Getx() { return x; }
        void Setx(int val) { x = val; setModified(true); }
        int Gety() { return y; }
        void Sety(int val) { y = val; setModified(true); }
        bool isModified() { return modified; }
        void setModified(bool val) { modified = val; }

        void setAlpha(bool, int);
        void hide() { setAlpha(true, 0); setModified(true); }
        void show() { setAlpha(false, 0); setModified(true); }

    protected:
        SDL_Surface *surface;
        int x;
        int y;
        int disp_w;
        int disp_h;
        bool modified;

    private:
};

#endif // SURFACE_H
