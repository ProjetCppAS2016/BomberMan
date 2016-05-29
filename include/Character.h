#ifndef CHARACTER_H
#define CHARACTER_H

#include "Structures.h"
#include "Sprite.h"


class Character
{
    public:
        Character();
        Character(int x, int y, int g_x, int g_y, Sprite* spt_L, Sprite* spt_R,Sprite* spt_U,Sprite* spt_D, TILE* tab[][GRID_SIZE]);
        ~Character();
        Character(const Character& other);
        Character& operator=(const Character& rhs);

        int Getx() { return x; }
        void Setx(int val);
        int Gety() { return y; }
        void Sety(int val);
        int Getgrid_x() { return grid_x; }
        void Setgrid_x(int val) { grid_x = val; }
        int Getgrid_y() { return grid_y; }
        void Setgrid_y(int val) { grid_y = val; }
        Sprite* getSpriteLeft() { return spriteLeft; }
        Sprite* getSpriteRight() { return spriteRight; }
        Sprite* getSpriteUp() { return spriteUp; }
        Sprite* getSpriteDown() { return spriteDown; }

        void deplacer(moves direction);
        void useSprite(moves direction, int nbrImg);

    protected:

    private:
        int x, y, sizeX, sizeY, grid_x, grid_y;
        Sprite *spriteLeft;
        Sprite *spriteRight;
        Sprite *spriteUp;
        Sprite *spriteDown;
        TILE* grid[GRID_SIZE][GRID_SIZE];
};

#endif // CHARACTER_H









