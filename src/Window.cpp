#include "Window.h"
#include "Surface.h"
#include "Screen.h"
#include <SDL/SDL.h>
#include <iostream>

using namespace std;

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












