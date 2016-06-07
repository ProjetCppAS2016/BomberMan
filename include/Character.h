#ifndef CHARACTER_H
#define CHARACTER_H

#include "Sprite.h"
#include "Structures.h"
#include "Screen.h"
#include <SDL/SDL.h>

class Character
{
    public:
        Character();
        Character(int g_x, int g_y, HITBOX htb, Sprite* spt_L, Sprite* spt_R, Sprite* spt_U,Sprite* spt_D, TILE* tab[][GRID_SIZE]);
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
        void CanDrop(bool val) { can_drop = val; }
        bool isAlive() { return alive; }
        void setAlive(bool val) { alive = val; }

        void moveTo(moves direction);
        void useSprite(moves direction, int nbrImg);
        void increaseX(int amount);
        void increaseY(int amount);
        void dropBomb();
        void kill();

    protected:

    private:
        int x, y, grid_x, grid_y;
        HITBOX hitbox;
        Sprite *spriteLeft;
        Sprite *spriteRight;
        Sprite *spriteUp;
        Sprite *spriteDown;
        TILE* grid[GRID_SIZE][GRID_SIZE];
        moves actualMove;
        bool can_drop;
        bool alive;
};

#endif // CHARACTER_H









