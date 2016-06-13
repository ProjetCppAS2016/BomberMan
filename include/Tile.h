#ifndef TILE_H
#define TILE_H

#include "Structures.h"
#include "Character.h"
#include "BMPSurface.h"

class Tile
{
    public:
        Tile();
        Tile(HITBOX htbx, content ctnt);
        ~Tile();
        Tile(const Tile& other);
        Tile& operator=(const Tile& other);

        HITBOX getHitbox() { return hitbox; }
        content getContent() { return contain; }
        BMPSurface* getBox() { return box; }
        void setHitbox(HITBOX val) { hitbox = val; }
        void setContent(content val) { contain = val; }
        void setBomber(Character *val) { bomber = val; }

        bool isInTile(HITBOX htbx);
        void destroy_Box();
        void kill_bomber();

    protected:

    private:
        HITBOX hitbox;
        content contain;
        BMPSurface *texture, *box;
        Character *bomber;
};

#endif // TILE_H









