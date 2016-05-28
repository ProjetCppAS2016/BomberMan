#include "Screen.h"
#include <iostream>

using namespace std;

SYNC* Screen::synchronization = new (SYNC);

void Screen::lockSync()
{ pthread_mutex_lock(synchronization->m_sync);
synchronization->locked=true; }

void Screen::unlockSync()
{ pthread_mutex_unlock(synchronization->m_sync);
synchronization->locked=false; }

void Screen::synchronise(int delay)
{
    if (synchronization->locked) {
        if (synchronization->cond_locked)
            pthread_mutex_lock(synchronization->m_sync);
        synchronization->cond_locked = true;
        pthread_cond_wait(synchronization->c_sync, synchronization->m_sync);
        pthread_mutex_unlock(synchronization->m_sync);
        synchronization->cond_locked = false;
    }
    SDL_Delay(delay);
}


void Screen::t_init()
{
    scr_mutexes = new(MUTEX);
    scr_mutexes->m_components = new (pthread_mutex_t);
    scr_mutexes->m_screen = new (pthread_mutex_t);
    synchronization->m_sync = new (pthread_mutex_t);
    synchronization->c_sync = new (pthread_cond_t);
    pthread_mutex_init(scr_mutexes->m_components, NULL);
    pthread_mutex_init(scr_mutexes->m_screen, NULL);
    pthread_mutex_init(synchronization->m_sync, NULL);
    pthread_cond_init(synchronization->c_sync, NULL);
    synchronization->cond_locked = synchronization->locked = false;
}

Screen::Screen() : Surface(), listComponents(NULL), auto_refresh(false), fps(40)
{ t_init(); }

Screen::Screen(SDL_Surface *s) : Surface(s), listComponents(NULL), auto_refresh(false), fps(40)
{ t_init(); }

Screen::~Screen()
{
    deleteAllComponents();
    if (auto_refresh) {
        auto_refresh = false;
        pthread_join(thread_ar, NULL);
    }
    pthread_mutex_destroy(scr_mutexes->m_components);
    pthread_mutex_destroy(scr_mutexes->m_screen);
    pthread_mutex_destroy(synchronization->m_sync);
    pthread_cond_destroy(synchronization->c_sync);
    delete(synchronization);
    delete(scr_mutexes);
}

Screen::Screen(const Surface& other) {}
Screen& Screen::operator=(const Surface&) { return *this; }

void Screen::setBgColor(int r, int g, int b)
{
    bgColor = SDL_MapRGB(surface->format, r, g, b);
    SDL_FillRect(surface, NULL, bgColor);
    SDL_Flip(surface);
}

void Screen::blit(Surface& component)
{
    SDL_Rect position;
    position.x = component.Getx();
    position.y = component.Gety();
    if (component.getDisp_h()!=-1)
        position.h = component.getDisp_h();
    if (component.getDisp_w()!=-1)
        position.w = component.getDisp_w();

    SDL_BlitSurface(component.getSurface(), NULL, surface, &position);
}
void Screen::delall(COMPONENT *t)
{
    if (t->next!=NULL) delall(t->next);

    SDL_Surface *tmp_s = new SDL_Surface;
    *tmp_s = *(t->object->getSurface());
    SDL_FreeSurface(t->object->getSurface());
    t->object->setSurface(tmp_s);
    delete t;
}
void Screen::refscr(COMPONENT *t)
{
    if (t!=NULL) {
        if (t->next!=NULL) refscr(t->next);

        blit(*(t->object));
    }
}

void Screen::addComponent(Surface& component)
{
    pthread_mutex_lock(scr_mutexes->m_components);
    pthread_mutex_lock(scr_mutexes->m_screen);

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

    pthread_mutex_unlock(scr_mutexes->m_components);
    pthread_mutex_unlock(scr_mutexes->m_screen);
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
    pthread_mutex_lock(scr_mutexes->m_components);

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

    pthread_mutex_unlock(scr_mutexes->m_components);
}

void Screen::deleteAllComponents()
{
    pthread_mutex_lock(scr_mutexes->m_components);

    if (listComponents!=NULL) {
        delall(listComponents);
    }

    pthread_mutex_unlock(scr_mutexes->m_components);
}

void Screen::clearScreen()
{
    pthread_mutex_lock(scr_mutexes->m_screen);

    SDL_FillRect(surface, NULL, bgColor);
    const int taille = listStaticsComponents.size();
    for (int i=0; i<taille; i++)
        blit(*(listStaticsComponents[i]));

    pthread_mutex_unlock(scr_mutexes->m_screen);
}

void Screen::refresh()
{
    pthread_mutex_lock(scr_mutexes->m_components);

    if (listComponents != NULL) {
        clearScreen();
        refscr(listComponents);
        SDL_Flip(surface);
    }

    pthread_mutex_unlock(scr_mutexes->m_components);
}

void Screen::refreshAll()
{
    pthread_mutex_lock(scr_mutexes->m_components);

    COMPONENT *tmp = listComponents;
    clearScreen();
    while (tmp!=NULL) {
        blit(*(tmp->object));
        tmp = tmp->next;
    }
    SDL_Flip(surface);

    pthread_mutex_unlock(scr_mutexes->m_components);
}

void* autoref(void* scr)
{
    Screen *screen = (Screen*) scr;
    int fps = screen->getFps();
    while (screen->hasAuto_refresh()) {
            Screen::lockSync();
            SDL_Delay(fps);
            Screen::broadcastSync();
            Screen::unlockSync();
            screen->refresh();
    }
    return NULL;
}

void Screen::activateA_R(bool activated)
{
    if (activated && !auto_refresh) {
        auto_refresh = true;
        pthread_create(&thread_ar, NULL, autoref, this);
    } else if (!activated && auto_refresh) {
        auto_refresh = false;
        pthread_join(thread_ar, NULL);
    }
}











