#ifndef CHARACTER_H
#define CHARACTER_H

#include "Structures.h"


class Character
{
    public:
        Character();
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
        TILE Getgrid() { return grid; }
        void Setgrid(TILE val) { grid = val; }

    protected:

    private:
        int x;
        int y;
        int grid_x;
        int grid_y;
        TILE grid;
};

#endif // CHARACTER_H
