#ifndef CHARACTER_H
#define CHARACTER_H

#include "Sprite.h"
#include "Structures.h"
#include "Screen.h"
#include "Grid.h"
#include <SDL/SDL.h>

class Character
{
    public:
        Character();
        Character(int x, int y, HITBOX htb, Grid *grd);
        ~Character();
        Character(const Character& other);
        Character& operator=(const Character& rhs);

        int Getx() { return x; }
        void Setx(int val);
        int Gety() { return y; }
        void Sety(int val);
        moves getMove() { return actualMove; }
        HITBOX getHitbox() { return hitbox; }
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
        int x, y;
        HITBOX hitbox;
        Grid *gameGrid;
        Sprite *spriteLeft;
        Sprite *spriteRight;
        Sprite *spriteUp;
        Sprite *spriteDown;
        moves actualMove;
        bool can_drop;
        bool alive;
};

#endif // CHARACTER_H









