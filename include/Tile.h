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
        Character* getBomber() { return bomberman; }
        void setHitbox(HITBOX val) { hitbox = val; }
        void setContent(content val) { contain = val; }
        void setBomber(Character *val) { bomberman = val; }

        bool inTile_top(hitbox htbx);
        bool inTile_bottom(hitbox htbx);
        bool inTile_left(hitbox htbx);
        bool inTile_right(hitbox htbx);
        void destroy_Box();

    protected:

    private:
        HITBOX hitbox;
        content contain;
        BMPSurface *texture, *box;
        Character *bomberman;
};

#endif // TILE_H









