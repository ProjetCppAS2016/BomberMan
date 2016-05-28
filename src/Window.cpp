#include "Window.h"
#include "Surface.h"
#include "Screen.h"
#include <SDL/SDL.h>
#include <iostream>

using namespace std;

Window* Window::instance = NULL;

Window::Window(int w, int h, string t, string i) : width(w), height(h), title(t), icon(i)
{
    SDL_Surface *s;
    if (icon.getSurface()!=NULL)
        SDL_WM_SetIcon(icon.getSurface(), NULL);
    s = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (s==NULL) {
        fprintf(stderr, "Erreur dans l'initialisation de la fenêtre: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    } else screen = new Screen(s);
    SDL_WM_SetCaption(title.c_str(), NULL);
}

Window::~Window()
{}

Window& Window::newInstance(int height, int width, string title, string icon)
{
    if (instance==NULL) {
        instance = new Window(height, width, title, icon);
        return *instance;
    } else return *instance;
}

void Window::waitEvent(Uint8 e)
{
    bool flag = false;
    SDL_Event event;

    while (!flag) {
        SDL_WaitEvent(&event);
        if (event.type == e)
            flag = true;
    }
}

void Window::showCursor(bool show)
{
    if (show)
        SDL_ShowCursor(SDL_ENABLE);
    else
        SDL_ShowCursor(SDL_DISABLE);
}












