#ifndef GRID_H
#define GRID_H

#include "Structures.h"
#include "Character.h"
#include "Tile.h"

class Grid
{
    public:
        Grid();
        ~Grid();
        Grid(const Grid& other);
        Grid& operator=(const Grid& other);

        Tile* getTile(int x, int y) { return tileTab[x][y]; };
        int getBmbX() { return bmbX; }
        int getBmbY() { return bmbY; }

        bool collision(Character *bomber);
        bool collision_exp(int x, int y);

    protected:

    private:
        Tile* tileTab[GRID_SIZE][GRID_SIZE];
        int bmbX, bmbY;
};

#endif // GRID_H














