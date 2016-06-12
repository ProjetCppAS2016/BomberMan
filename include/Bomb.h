#ifndef BOMB_H
#define BOMB_H

#include "Sprite.h"
#include "Structures.h"
#include "Character.h"
#include "Explosion.h"
#include "Grid.h"
#include <pthread.h>

class Bomb
{
    public:
        Bomb();
        Bomb(int grid_x, int grid_y, Grid *gameGrid, Character *thrower);
        ~Bomb();
        Bomb(const Bomb& other);
        Bomb& operator=(const Bomb& rhs);

        int getGrid_x() { return grid_x; }
        int getGrid_y() { return grid_y; }
        Sprite* getBomb_spt() { return bomb_spt; }
        Character *getThrower() { return thrower; }

        void explode();

    protected:

    private:
        int grid_x, grid_y;
        Grid *gameGrid;
        pthread_t thread;
        Sprite *bomb_spt;
        Character *thrower;
};

#endif // BOMB_H









