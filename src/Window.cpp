#include "Window.h"
#include "Surface.h"
#include "Screen.h"
#include <SDL/SDL.h>
#include <iostream>

using namespace std;

void Window::init()
{
    SDL_Surface *s;
    if (icon.getSurface()!=NULL)
        SDL_WM_SetIcon(icon.getSurface(), NULL);
    s = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE);
    if (s==NULL) {
        fprintf(stderr, "Erreur dans l'initialisation de la fenêtre: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    } else screen = new Screen(s);
}

Window::Window(int w, int h) : width (w), height(h), icon()
{
    init();
}
Window::Window(int w, int h, string t) : width (w), height(h), title(t), icon()
{
    init();
    SDL_WM_SetCaption(title.c_str(), NULL);
}
Window::Window(int w, int h, string t, string i) : width (w), height(h), title(t), icon(i)
{
    init();
    SDL_WM_SetCaption(title.c_str(), NULL);
}


Window::~Window()
{}

Window::Window(const Window& other) : width (other.width),
                                        height(other.height),
                                        title(other.title),
                                        icon(other.icon)
{ screen = new Screen(*(other.screen)); }


void Window::WaitEvent(Uint8 e)
{
    bool flag = false;
    SDL_Event event;

    while (!flag) {
        SDL_WaitEvent(&event);
        if (event.type == e)
            flag = true;
    }
}












