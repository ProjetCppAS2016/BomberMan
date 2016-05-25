#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED
#include <pthread.h>
#include "Surface.h"

enum moves { LEFT, RIGHT, UP, DOWN };
enum content { WALL, D_WALL, NTHG };

typedef struct COMPONENT
{
    COMPONENT* prev;
    COMPONENT* next;
    Surface *object;
} COMPONENT;

typedef struct MUTEX
{
    pthread_mutex_t *m_screen;
    pthread_mutex_t *m_components;
} MUTEX;

typedef struct SYNC
{
    bool locked, cond_locked;
    pthread_mutex_t *m_sync;
    pthread_cond_t *c_sync;
} SYNC;

typedef struct TILE
{
    int xMin, xMax, yMin, yMax;
    content contain;
} TILE;

#endif // STRUCTURES_H_INCLUDED
