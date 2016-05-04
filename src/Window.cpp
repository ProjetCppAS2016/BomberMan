#include "Window.h"
#include "Surface.h"
#include <SDL/SDL.h>
#include <iostream>

using namespace std;

Window::Window(int w, int h, int d) : width (w), height(h), depth(d)
{
    SDL_Surface *s;
    s = SDL_SetVideoMode(width, height, depth, SDL_HWSURFACE);
    if (s==NULL) {
        cout << "Erreur dans l'initialisation de la fenêtre: " << SDL_GetError();
        exit(EXIT_FAILURE);
    } else screen = new Surface(s);
}

Window::Window(int w, int h, int d, string t) : width (w), height(h), depth(d), title(t)
{
    SDL_Surface *s;
    s = SDL_SetVideoMode(width, height, depth, SDL_HWSURFACE);
    if (s==NULL) {
        cout << "Erreur dans l'initialisation de la fenêtre: " << SDL_GetError();
        exit(EXIT_FAILURE);
    } else screen = new Surface(s);
    SDL_WM_SetCaption((char*) &title, NULL);
}

Window::~Window()
{}

Window::Window(const Window& other)
{
    depth = other.depth;
    width = other.width;
    height = other.height;
}
int Window::getWidth() { return width; }
int Window::getHeight() { return height; }
int Window::getDepth() { return depth; }
void Window::setTitle(string t) { title = t; SDL_WM_SetCaption((char*) &title, NULL); }
string Window::getTitle() { return title; }



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

void Window::setBgColor(int r, int g, int b)
{
    SDL_FillRect(screen->getSurface(), NULL, SDL_MapRGB(screen->getSurface()->format, r, g, b));
    SDL_Flip(screen->getSurface());
}

void Window::addComponent(Surface* component)
{
    content.push_back(component);
}













