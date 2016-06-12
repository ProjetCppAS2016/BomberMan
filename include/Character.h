#ifndef CHARACTER_H
#define CHARACTER_H

#include "Sprite.h"
#include "Structures.h"
#include "Window.h"
#include <sstream>
#include <iostream>

class Character
{
    public:
        Character();
        Character(int x, int y, HITBOX htb);
        ~Character();
        Character(const Character& other);
        Character& operator=(const Character& rhs);

        int Getx() { return x; }
        void Setx(int val);
        int Gety() { return y; }
        void Sety(int val);
        moves getMove() { return actualMove; }
        HITBOX getHitbox() { return hitbox; }
        void CanDrop(bool val) { can_drop = val; }
        bool isAlive() { return alive; }
        void setAlive(bool val) { alive = val; }

        void useSprite(moves direction, int nbrImg);
        void increaseX(int amount);
        void increaseY(int amount);
        void kill();

    protected:
        int x, y;
        HITBOX hitbox;
        Sprite *spriteLeft;
        Sprite *spriteRight;
        Sprite *spriteUp;
        Sprite *spriteDown;
        moves actualMove;
        bool can_drop;
        bool alive;
        int time_drop;

    private:
};

#endif // CHARACTER_H









