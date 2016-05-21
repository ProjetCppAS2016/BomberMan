#include "Screen.h"

SDL_mutex* Screen::m_sync = SDL_CreateMutex();
SDL_cond* Screen::c_sync = SDL_CreateCond();

Screen::Screen() : Surface(), listComponents(NULL), auto_refresh(0), thread_ar(NULL), fps(25)
{ t_init(); }
Screen::Screen(SDL_Surface *s) : Surface(s), listComponents(NULL), auto_refresh(0), thread_ar(NULL), fps(25)
{ t_init(); }

Screen::~Screen()
{
    deleteAllCompenents();
    SDL_DestroyMutex(scr_mutexes->m_components);
    SDL_DestroyMutex(scr_mutexes->m_screen);
    SDL_DestroyMutex(m_sync);
    delete(scr_mutexes);
    auto_refresh = false;
    if (thread_ar != NULL) SDL_WaitThread(thread_ar, NULL);
}

Screen::Screen(const Screen& other) : Surface(other), listComponents(NULL), auto_refresh(0), fps(other.fps)
{ t_init(); }


void Screen::setBgColor(int r, int g, int b)
{
    bgColor = SDL_MapRGB(surface->format, r, g, b);
    SDL_FillRect(surface, NULL, bgColor);
    SDL_Flip(surface);
}

void Screen::addComponent(Surface& component)
{
    SDL_mutexP(scr_mutexes->m_components);
    SDL_mutexP(scr_mutexes->m_screen);

    if (listComponents==NULL) {
        listComponents = (COMPONENT*) malloc(sizeof(COMPONENT));
        listComponents->object = &component;
        listComponents->next = NULL;
        listComponents->prev = NULL;
    } else {
        listComponents->prev = (COMPONENT*) malloc(sizeof(COMPONENT));
        listComponents->prev->next = listComponents;
        listComponents = listComponents->prev;
        listComponents->object = &component;
        listComponents->prev = NULL;
    }

    blit(component);
    SDL_Flip(surface);

    SDL_mutexV(scr_mutexes->m_components);
    SDL_mutexV(scr_mutexes->m_screen);
}

void Screen::addStaticComponent(Surface& component)
{
    listStaticsComponents.push_back(&component);
    blit(component);
    SDL_Flip(surface);
}
void Screen::deleteStaticComponent()
{
    listStaticsComponents.pop_back();
    refresh();
    SDL_Flip(surface);
}

void Screen::deleteComponent(Surface* component)
{
    SDL_mutexP(scr_mutexes->m_components);

    COMPONENT *tmp = listComponents;
    SDL_Surface *tmp_s = new SDL_Surface;
    while (tmp!=NULL && (Surface*) &(tmp->object)!=component)
        tmp = tmp->next;
    if (tmp!=NULL) {
        tmp->prev->next = tmp->next;
        if (tmp->next != NULL)
            tmp->next->prev = tmp->prev;

        *tmp_s = *(tmp->object->getSurface());
        SDL_FreeSurface(tmp->object->getSurface());
        tmp->object->setSurface(tmp_s);
        delete tmp;
    }

    SDL_mutexV(scr_mutexes->m_components);
}

void Screen::deleteAllCompenents()
{
    SDL_mutexP(scr_mutexes->m_components);

    if (listComponents!=NULL) {
        delall(listComponents);
    }

    SDL_mutexV(scr_mutexes->m_components);
}

void Screen::clearScreen()
{
    SDL_mutexP(scr_mutexes->m_screen);

    SDL_FillRect(surface, NULL, bgColor);
    const int taille = listStaticsComponents.size();
    for (int i=0; i<taille; i++)
        blit(*(listStaticsComponents[i]));

    SDL_mutexV(scr_mutexes->m_screen);
}

void Screen::refresh()
{
    SDL_mutexP(scr_mutexes->m_components);

    if (listComponents != NULL) {
        clearScreen();
        refscr(listComponents);
        SDL_Flip(surface);
    }

    SDL_mutexV(scr_mutexes->m_components);
}

void Screen::refreshAll()
{
    SDL_mutexP(scr_mutexes->m_components);

    COMPONENT *tmp = listComponents;
    clearScreen();
    while (tmp!=NULL) {
        blit(*(tmp->object));
        tmp = tmp->next;
    }
    SDL_Flip(surface);

    SDL_mutexV(scr_mutexes->m_components);
}

int ar_thread(void* scr)
{
    Screen *screen = (Screen*) scr;
    screen->activateA_R(true);
    return 0;
}

void Screen::activateA_R(bool activated)
{
    if (activated && auto_refresh==0) {
        auto_refresh = 1;
        thread_ar = SDL_CreateThread(ar_thread, this);
    } else if (activated && auto_refresh==1) {
        auto_refresh = 2;
        while (auto_refresh) {
            SDL_mutexP(m_sync);
            SDL_Delay(fps);
            SDL_mutexV(m_sync);
            SDL_CondBroadcast(c_sync);
            refresh();
        }
    } else if (!activated && auto_refresh==2) {
        auto_refresh = 0;
        if (thread_ar != NULL) SDL_WaitThread(thread_ar, NULL);
    }
}











