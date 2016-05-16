#include "Screen.h"

Screen::Screen() : Surface(), listComponents(NULL)
{}
Screen::Screen(SDL_Surface *s) : Surface(s), listComponents(NULL)
{}

Screen::~Screen()
{ deleteAllCompenents(); }

Screen::Screen(const Screen& other) : Surface(other), listComponents(NULL)
{}


void Screen::setBgColor(int r, int g, int b)
{
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, r, g, b));
    SDL_Flip(surface);
}

void Screen::addComponent(Surface& component)
{
    if (listComponents==NULL) {
        listComponents = (COMPONENT*) malloc(sizeof(COMPONENT));
        listComponents->object = component;
        listComponents->next = NULL;
        listComponents->prev = NULL;
    } else {
        listComponents->prev = (COMPONENT*) malloc(sizeof(COMPONENT));
        listComponents->prev->next = listComponents;
        listComponents = listComponents->prev;
        listComponents->object = component;
        listComponents->prev = NULL;
    }

    blit(component);
    SDL_Flip(surface);
}

void Screen::addStaticComponent(Surface& component)
{
    blit(component);
    SDL_Flip(surface);
}

void Screen::deleteComponent(Surface* component)
{
    COMPONENT *tmp = listComponents;
    SDL_Surface *tmp_s = new SDL_Surface;
    while (tmp!=NULL && (Surface*) &(tmp->object)!=component)
        tmp = tmp->next;
    if (tmp!=NULL) {
        tmp->prev->next = tmp->next;
        if (tmp->next != NULL)
            tmp->next->prev = tmp->prev;

        *tmp_s = *(tmp->object.getSurface());
        SDL_FreeSurface(tmp->object.getSurface());
        tmp->object.setSurface(tmp_s);
        delete tmp;
        SDL_Flip(surface);
    }
}

void Screen::deleteAllCompenents()
{
    if (listComponents!=NULL) {
        delall(listComponents);
        SDL_Flip(surface);
    }
}

void Screen::refresh()
{
    if (listComponents != NULL) {
        refscr(listComponents);
        SDL_Flip(surface);
    }
}

void Screen::refreshAll()
{
    COMPONENT *tmp = listComponents;
    while (tmp!=NULL) {
        blit(tmp->object);
        tmp = tmp->next;
    }
    SDL_Flip(surface);
}







