#ifndef BOMB_H
#define BOMB_H

#include "Sprite.h"
#include "BMPSurface.h"
#include "Structures.h"
#include "Character.h"
#include <pthread.h>
#include <SDL/SDL.h>

class Bomb
{
    public:
        Bomb();
        Bomb(int grid_x, int grid_y, int force, TILE *grid[GRID_SIZE][GRID_SIZE], Character *thrower);
        ~Bomb();
        Bomb(const Bomb& other);
        Bomb& operator=(const Bomb& rhs);

        int getGrid_x() { return grid_x; }
        int getGrid_y() { return grid_y; }
        Sprite* getBomb_spt() { return bomb_spt; }
        int getForce() { return force; }
        Character *getThrower() { return thrower; }

        void explode(int left, int right, int up, int down, int i_explosion);

    protected:

    private:
        int grid_x, grid_y, force;
        TILE *grid[GRID_SIZE][GRID_SIZE];
        pthread_t thread;
        Sprite *bomb_spt;
        Character *thrower;
};

#endif // BOMB_H









