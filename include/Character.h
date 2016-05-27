#ifndef CHARACTER_H
#define CHARACTER_H

#include "Structures.h"


class Character
{
    public:
        Character();
        Character(int x, int y, int g_x, int g_y, TILE* tab[][GRID_SIZE]);
        ~Character();
        Character(const Character& other);

        int Getx() { return x; }
        void Setx(int val) { x = val; }
        int Gety() { return y; }
        void Sety(int val) { y = val; }
        int Getgrid_x() { return grid_x; }
        void Setgrid_x(int val) { grid_x = val; }
        int Getgrid_y() { return grid_y; }
        void Setgrid_y(int val) { grid_y = val; }

        void deplacer(moves direction);

    protected:

    private:
        int x, y, sizeX, sizeY, grid_x, grid_y;
        TILE* grid[GRID_SIZE][GRID_SIZE];
};

#endif // CHARACTER_H
