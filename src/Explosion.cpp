#include "Explosion.h"

using namespace std;

Explosion::Explosion() : pos_x(0), pos_y(0), direction(STOP), canPropagate(false), gameGrid(NULL), texture(NULL), next_explosion(NULL)
{}

Explosion::Explosion(int x, int y, moves dir, Grid *gameGd) : pos_x(x), pos_y(y), direction(dir),
                                                              gameGrid(gameGd), canPropagate(false),
                                                              texture(NULL), next_explosion(NULL)
{
    string path;
    switch (direction)
    {
    case LEFT:
        path = "textures\\explosion_left.bmp";
        pos_x--;
        break;
    case RIGHT:
        path = "textures\\explosion_right.bmp";
        pos_x++;
        break;
    case UP:
        path = "textures\\explosion_up.bmp";
        pos_y--;
        break;
    case DOWN:
        path = "textures\\explosion_down.bmp";
        pos_y++;
        break;
    case STOP:
        path = "textures\\explosion_center.bmp";
    }
    if (!gameGrid->collision_exp(pos_x, pos_y)) {
        canPropagate = true;
        HITBOX htbx = gameGrid->getTile(pos_x,pos_y)->getHitbox();
        texture = new BMPSurface(path, htbx.xMin, htbx.yMin);
        texture->setTransparency(true, 0, 255, 0);
        Window::getScreen().addComponent(texture);
    }
}

Explosion::~Explosion()
{
    delete next_explosion;
    Window::getScreen().deleteComponent(texture);
    if (canPropagate) gameGrid->getTile(pos_x, pos_y)->setContent(NTHG);
}

Explosion::Explosion(const Explosion& other): pos_x(other.pos_x), pos_y(other.pos_y),
                                              direction(other.direction),
                                              canPropagate(other.canPropagate),
                                              gameGrid(other.gameGrid), next_explosion(NULL)
{
    string path;
    HITBOX htbx = gameGrid->getTile(pos_x,pos_y)->getHitbox();
    switch (direction)
    {
    case LEFT:
        path = "textures\\explosion_left.bmp";
        break;
    case RIGHT:
        path = "textures\\explosion_right.bmp";
        break;
    case UP:
        path = "textures\\explosion_up.bmp";
        break;
    case DOWN:
        path = "textures\\explosion_down.bmp";
        break;
    case STOP:
        path = "textures\\explosion_center.bmp";
    }
    texture = new BMPSurface(path, htbx.xMin, htbx.yMin);
    Window::getScreen().addComponent(texture);
}

void Explosion::propagate()
{
    if (canPropagate) {
        if (direction == STOP) {
            Explosion *e_left, *e_right, *e_up, e_down;
            e_left = new Explosion(pos_x-1, pos_y, LEFT, gameGrid);
            e_right = new Explosion(pos_x+1, pos_y, RIGHT, gameGrid);
            e_up = new Explosion(pos_x, pos_y-1, UP, gameGrid);
            e_down = new Explosion(pos_x, pos_y+1, DOWN, gameGrid);

            for (int i=0; i<3; i++) {
                e_left->propagate();
                e_right->propagate();
                e_up->propagate();
                e_down->propagate();
                SDL_Delay(200);
            }
            SDL_Delay(1000);
            delete e_left;
            delete e_right;
            delete e_up;
            delete e_down;
        } else {
            if (next_explosion==NULL)
                next_explosion = new Explosion(pos_x, pos_y, direction, gameGrid);
            else next_explosion->propagate();
        }
    }
}















