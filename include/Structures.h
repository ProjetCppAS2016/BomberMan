#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include <pthread.h>
#include "Surface.h"
#include "BMPSurface.h"

#define GRID_SIZE 11

enum moves { LEFT, RIGHT, UP, DOWN, STOP };
enum content { WALL, BOX, NTHG, EXPLOSION };

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



typedef struct HITBOX
{
    int xMin;
    int xMax;
    int yMin;
    int yMax;
} HITBOX;


#endif // STRUCTURES_H_INCLUDED
