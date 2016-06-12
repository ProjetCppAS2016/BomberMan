#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Grid.h"
#include "BMPSurface.h"
#include "Structures.h"
#include <SDL/SDL.h>

class Explosion
{
    public:
        Explosion();
        Explosion(int pos_x, int pos_y, moves direction, Grid *gameGrid);
        ~Explosion();
        Explosion(const Explosion& other);

        void propagate();

    protected:

    private:
        int pos_x, pos_y;
        moves direction;
        bool canPropagate;
        Grid *gameGrid;
        BMPSurface *texture;
        Explosion *next_explosion;
};

#endif // EXPLOSION_H












