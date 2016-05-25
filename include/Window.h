#ifndef WINDOW_H
#define WINDOW_H
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include <iostream>
#include <vector>
#include "Surface.h"
#include "Screen.h"
#include "BMPSurface.h"

class Window
{
    public:
        Window(int height, int width);
        Window(int height, int width, std::string title);
        Window(int height, int width, std::string title, std::string icon);
        virtual ~Window();
        Window(const Window& other);

        int getWidth() { return width; }
        int getHeight() { return height; }
        void setTitle(std::string t) { title = t; SDL_WM_SetCaption((char*) &title, NULL); }
        std::string getTitle() { return title; }
        Screen& getScreen() { return (*screen); }

        void waitEvent(Uint8 event);
        void showCursor(bool value);

    protected:

    private:
        int width;
        int height;
        Screen* screen;
        std::string title;
        BMPSurface icon;
        void init()
        {
            SDL_Surface *s;
            if (icon.getSurface()!=NULL)
                SDL_WM_SetIcon(icon.getSurface(), NULL);
            s = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
            if (s==NULL) {
                fprintf(stderr, "Erreur dans l'initialisation de la fenêtre: %s", SDL_GetError());
                exit(EXIT_FAILURE);
            } else screen = new Screen(s);
        }
};

#endif // WINDOW_H





