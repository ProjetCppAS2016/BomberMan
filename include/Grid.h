#ifndef GRID_H
#define GRID_H

#include "Structures.h"
#include "Tile.h
#include "Character.h"
#include "Bomb.h"

class Grid
{
    public:
        Grid();
        ~Grid();
        Grid(const Grid& other);
        Grid& operator=(const Grid& other);

        Tile* getTile(int x, int y) { return &(tileTab[x][y]); };
        Tile* getGrid() { return &tileTab; }
        int getBmbX() { return bmbX; }
        int getBmbY() { return bmbY; }
        Character* getBomber(int x, int y) { return tileTab[x][y].getBomber(); }

        bool collision(Character* bomberman);
        bool collision(Bomb* bomb);

    protected:

    private:
        Tile tileTab[GRID_SIZE][GRID_SIZE];
        int bmbX, bmbY;
};

#endif // GRID_H














