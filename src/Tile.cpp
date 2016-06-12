#include "Tile.h"

using namespace std;

Tile::Tile() : hitbox({0,0,0,0}), contain(NTHG), texture(NULL); box(NULL), bomberman(NULL)
{}

Tile::Tile(HITBOX htbx, content ctnt) : hitbox(htbx), contain(ctnt), box(NULL), bomberman(NULL)
{
    if (contain == WALL)
        texture = new BMPSurface("textures\\wall.bmp", hitbox.xMin, hitbox.yMin);
    else {
        texture = new BMPSurface("textures\\floor.bmp", hitbox.xMin, hitbox.yMin);
        if (contain == BOX) {
            box = new BMPSurface("textures\\box.bmp", hitbox.xMin, hitbox.yMin);
            Window::getScreen().addComponent(box);
        }
    }
    Window::getScreen().addStaticComponent(&texture);
}

Tile::~Tile()
{ Window::getScreen().deleteComponent(box); }

Tile::Tile(const Tile& other) : hitbox(other.htbx), contain(other.ctnt), texture(other.texture), box(other.box), bomberman(other.bomberman)
{}

Tile& Tile::operator=(const Tile& rhs)
{
    if (this == &rhs) return *this; // handle self assignment

    hitbox = rhs.htbx;
    contain = rhs.ctnt;
    texture = rhs.texture;
    box = rhs.box;
    bomberman = rhs.bomberman;
    return *this;
}

bool Tile::inTile_top(HITBOX bomber_htbx)
{
    if (bomber_htbx.xMax>=hitbox.xMin && bomber_htbx.xMin<=hitbox.xMax) {
        if (bomber_htbx.yMax >= hitbox.yMin)
            return true;
        else return false;
    } else return false;
}

bool Tile::inTile_bottom(HITBOX bomber_htbx)
{
    if (bomber_htbx.xMax>=hitbox.xMin && bomber_htbx.xMin<=hitbox.xMax) {
        if (bomber_htbx.yMin <= hitbox.yMax)
            return true;
        else return false;
    } else return false;
}

bool Tile::inTile_left(HITBOX bomber_htbx)
{
     if (bomber_htbx.yMax>=hitbox.yMin && bomber_htbx.yMin<=hitbox.yMax) {
        if (bomber_htbx.xMax >= hitbox.xMin)
            return true;
        else return false;
    } else return false;
}

bool Tile::inTile_right(HITBOX bomber_htbx)
{
    if (bomber_htbx.yMax>=hitbox.yMin && bomber_htbx.yMin<=hitbox.yMax) {
        if (bomber_htbx.yMin <= hitbox.yMax)
            return true;
        else return false;
    } else return false;
}

void Tile::destroy_Box()
{
    Window::getScreen()->deleteComponent(box);
    contain = NTHG;
}














