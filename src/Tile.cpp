#include "Tile.h"

using namespace std;

Tile::Tile() : hitbox({0,0,0,0}), contain(NTHG), texture(NULL), box(NULL), bomber(NULL)
{}

Tile::Tile(HITBOX htbx, content ctnt) : hitbox(htbx), contain(ctnt), box(NULL), bomber(NULL)
{
    if (contain == WALL)
        texture = new BMPSurface("textures\\wall.bmp", hitbox.xMin, hitbox.yMin);
    else {
        texture = new BMPSurface("textures\\floor.bmp", hitbox.xMin, hitbox.yMin);
        if (contain == BOX) {
            box = new BMPSurface("textures\\box.bmp", hitbox.xMin, hitbox.yMin);
            Window::getScreen().addComponent(box, false);
        }
    }
    Window::getScreen().addStaticComponent(texture, false);
}

Tile::~Tile()
{ Window::getScreen().deleteComponent(box); }

Tile::Tile(const Tile& other) : hitbox(other.hitbox), contain(other.contain), texture(other.texture), box(other.box), bomber(other.bomber)
{}

Tile& Tile::operator=(const Tile& rhs)
{
    if (this == &rhs) return *this; // handle self assignment

    hitbox = rhs.hitbox;
    contain = rhs.contain;
    texture = rhs.texture;
    box = rhs.box;
    bomber = rhs.bomber;
    return *this;
}

bool Tile::isInTile(HITBOX bomber_htbx)
{
    if (bomber_htbx.yMax>=hitbox.yMin && bomber_htbx.yMin<=hitbox.yMax &&
        bomber_htbx.xMin<=hitbox.xMax && bomber_htbx.xMax>=hitbox.xMin)
            return true;
    else return false;
}

void Tile::destroy_Box()
{
    Window::getScreen().deleteComponent(box);
    contain = NTHG;
}

void Tile::kill_bomber()
{ if (bomber!=NULL) bomber->kill(); }














