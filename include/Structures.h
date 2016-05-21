#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

typedef struct COMPONENT
{
    COMPONENT* prev;
    COMPONENT* next;
    Surface *object;
} COMPONENT;

typedef struct MUTEX
{
    SDL_mutex *m_screen;
    SDL_mutex *m_components;
} MUTEX;

/*typedef struct CONDITION
{
    SDL_cond *c_screen;
    SDL_cond *c_components;
} CONDITION;*/

#endif // STRUCTURES_H_INCLUDED
