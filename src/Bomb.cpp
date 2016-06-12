#include "Bomb.h"
#include "Character.h"
#include "Window.h"

using namespace std;

void* wait_explode(void* arg)
{
    Bomb *bomb = (Bomb*) arg;

    SDL_Delay(3000);
    Window::getScreen().deleteComponent(bomb->getBomb_spt());
    bomb->explode();
    return NULL;
}

Bomb::Bomb() : grid_x(0), grid_y(0), gameGrid(NULL), bomb_spt(NULL), thrower(NULL)
{}

Bomb::Bomb(int grid_x, int grid_y, Grid *gameGrid, Character *thrower): grid_x(grid_x), grid_y(grid_y),
                                                                        gameGrid(gameGrid), thrower(thrower)
{
    BMPSurface *tmp1 = new BMPSurface("textures\\bomb_1.bmp");
    BMPSurface *tmp2 = new BMPSurface("textures\\bomb_2.bmp");
    BMPSurface *tmp3 = new BMPSurface("textures\\bomb_3.bmp");
    tmp1->setTransparency(true, 0, 255, 0);
    tmp2->setTransparency(true, 0, 255, 0);
    tmp3->setTransparency(true, 0, 255, 0);
    bomb_spt = new Sprite(3, 1000, tmp1, tmp2, tmp3);

    HITBOX htbx = gameGrid->getTile(grid_x, grid_y)->getHitbox();
    bomb_spt->Setx(htbx.xMin);
    bomb_spt->Sety(htbx.yMin);
    bomb_spt->displaySprite(true);
    Window::getScreen().addComponent(bomb_spt, false);

    if (pthread_create(&thread, NULL, wait_explode, (void*) this))
        fprintf(stderr, "Bomb.cpp: Erreur dans la création du thread");
    else pthread_detach(thread);
}

Bomb::~Bomb()
{ Window::getScreen().deleteComponent(bomb_spt); }

Bomb::Bomb(const Bomb& other) : grid_x(other.grid_x), grid_y(other.grid_y), gameGrid(other.gameGrid), thrower(other.thrower)
{}

Bomb& Bomb::operator=(const Bomb& rhs)
{
    grid_x = rhs.grid_x;
    grid_y = rhs.grid_y;
    thrower = rhs.thrower;
    gameGrid = rhs.gameGrid;
    return *this;
}

void Bomb::explode()
{
    Explosion *explosion_center = new Explosion(grid_x, grid_y, STOP, gameGrid);
    explosion_center->propagate();
    delete explosion_center;
    thrower->CanDrop(true);
}















