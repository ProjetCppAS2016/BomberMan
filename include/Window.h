#ifndef WINDOW_H
#define WINDOW_H
#include <SDL/SDL.h>
#include <iostream>
#include <vector>
#include "Surface.h"
#include "Screen.h"
#include "BMPSurface.h"

class Window
{
    public:
        Window(int, int);
        Window(int, int, std::string);
        Window(int, int, std::string, std::string);
        void init();
        ~Window();
        Window(const Window& other);

        int getWidth() { return width; }
        int getHeight() { return height; }
        void setTitle(std::string t) { title = t; SDL_WM_SetCaption((char*) &title, NULL); }
        std::string getTitle() { return title; }
        Screen& getScreen() { return (*screen); }

        void waitEvent(Uint8);
        void showCursor(bool);

    protected:

    private:
        int width;
        int height;
        Screen* screen;
        std::string title;
        BMPSurface icon;
};

#endif // WINDOW_H





