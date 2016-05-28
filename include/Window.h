#ifndef WINDOW_H
#define WINDOW_H
#include <SDL/SDL.h>
#include <pthread.h>
#include <iostream>
#include <vector>
#include "Surface.h"
#include "Screen.h"
#include "BMPSurface.h"

class Window
{
    public:

        int getWidth() { return width; }
        int getHeight() { return height; }
        void setTitle(std::string t) { title = t; SDL_WM_SetCaption((char*) &title, NULL); }
        std::string getTitle() { return title; }
        Screen& getScreen() { return *screen; }

        static Window& newInstance(int height, int width, std::string title, std::string icon);
        static Window& getInstance() { return *instance; }
        static void destroy() { delete instance; }
        static void waitEvent(Uint8 event);
        static void showCursor(bool value);

    protected:

    private:
        static Window *instance;

        int width;
        int height;
        Screen* screen;
        std::string title;
        BMPSurface icon;

        Window(int h, int w, std::string t, std::string i);
        ~Window();
};

#endif // WINDOW_H





