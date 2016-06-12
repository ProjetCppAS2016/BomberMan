#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#include "Character.h"
#include "Screen.h"
#include "Grid.h"
#include "Bomb.h"
#include "Window.h"
#include <SDL/SDL.h>


class Bomberman : public Character
{
    public:
        Bomberman();
        Bomberman(int x, int y, HITBOX htb, Grid *gameGrid);
        virtual ~Bomberman();
        Bomberman(const Bomberman& other);

        void waitEvents();
        void moveTo(moves direction);
        void dropBomb();

    protected:

    private:
        Grid *gameGrid;
};

#endif // BOMBERMAN_H

















