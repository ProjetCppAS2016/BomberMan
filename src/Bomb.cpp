#include "Bomb.h"
#include "Character.h"
#include "Window.h"

using namespace std;

void* wait_explode(void* arg)
{
    Bomb *bomb = (Bomb*) arg;

    SDL_Delay(3000);
    Window::getInstance().getScreen()->deleteComponent(bomb->getBomb_spt());
    bomb->explode(1, 1, 1, 1, bomb->getForce());
    bomb->getThrower()->CanDrop(true);

    return NULL;
}

Bomb::Bomb() : grid_x(0), grid_y(0), force(0), bomb_spt(NULL), thrower(NULL)
{
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            grid[i][j] = NULL;
    }
}

Bomb::Bomb(int grid_x, int grid_y, int force, TILE *grid_tiles[GRID_SIZE][GRID_SIZE], Character *thrower):
           grid_x(grid_x), grid_y(grid_y), force(force), thrower(thrower)
{
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            grid[i][j] = grid_tiles[i][j];
    }
    BMPSurface *tmp1 = new BMPSurface("textures\\bomb_1.bmp");
    BMPSurface *tmp2 = new BMPSurface("textures\\bomb_2.bmp");
    BMPSurface *tmp3 = new BMPSurface("textures\\bomb_3.bmp");
    tmp1->setTransparency(true, 0, 255, 0);
    tmp2->setTransparency(true, 0, 255, 0);
    tmp3->setTransparency(true, 0, 255, 0);
    bomb_spt = new Sprite(3, 1000, tmp1, tmp2, tmp3);
    bomb_spt->Setx(grid[grid_x][grid_y]->xMin);
    bomb_spt->Sety(grid[grid_x][grid_y]->yMin);
    bomb_spt->displaySprite(true);
    Window::getInstance().getScreen()->addComponent(bomb_spt, false);

    if (pthread_create(&thread, NULL, wait_explode, (void*) this))
        fprintf(stderr, "Bomb.cpp: Erreur dans la création du thread");
    else pthread_detach(thread);
}

Bomb::~Bomb()
{ delete bomb_spt; }

Bomb::Bomb(const Bomb& other) : grid_x(other.grid_x), grid_y(other.grid_y), force(other.force), thrower(other.thrower)
{
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            grid[i][j] = other.grid[i][j];
    }
}


Bomb& Bomb::operator=(const Bomb& rhs)
{
    grid_x = rhs.grid_x;
    grid_y = rhs.grid_y;
    force = rhs.force;
    thrower = rhs.thrower;
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            grid[i][j] = rhs.grid[i][j];
    }
    return *this;
}

void Bomb::explode(int left, int right, int up, int down, int i_explosion)
{
    BMPSurface *tmp = NULL;
    Screen *screen = Window::getInstance().getScreen();
    if (i_explosion == force) {
        tmp = new BMPSurface("textures\\explosion_center.bmp", grid[grid_x][grid_y]->xMin, grid[grid_x][grid_y]->yMin);
        tmp->setTransparency(true, 0, 255, 0);
        screen->addComponent(tmp, false);
        if (grid[grid_x][grid_y]->player != NULL) {
            Character* bomberman = (Character*) (grid[grid_x][grid_y]->player);
            bomberman->setAlive(false);
        }
    }
    BMPSurface *exp_left=NULL, *exp_right=NULL, *exp_up=NULL, *exp_down=NULL;

    SDL_Delay(200);
    if (i_explosion!=0) {
        switch (grid[grid_x-left][grid_y]->contain)
        {
        case NTHG:
            if (grid[grid_x-left][grid_y]->player != NULL) {
                Character* bomberman = (Character*) (grid[grid_x-left][grid_y]->player);
                bomberman->setAlive(false);
            }
            exp_left = new BMPSurface("textures\\explosion_left.bmp", grid[grid_x-left][grid_y]->xMin, grid[grid_x-left][grid_y]->yMin);
            exp_left->setTransparency(true, 0, 255, 0);
            screen->addComponent(exp_left, false);
            left++;
            break;
        case BOX:
            screen->deleteComponent(grid[grid_x-left][grid_y]->box);
            grid[grid_x-left][grid_y]->box = NULL;
            grid[grid_x-left][grid_y]->contain = NTHG;
            exp_left = new BMPSurface("textures\\explosion_left.bmp", grid[grid_x-left][grid_y]->xMin, grid[grid_x-left][grid_y]->yMin);
            exp_left->setTransparency(true, 0, 255, 0);
            screen->addComponent(exp_left, false);
            left++;
            break;
        default:
            break;
        }
        switch (grid[grid_x+right][grid_y]->contain)
        {
        case NTHG:
            if (grid[grid_x+right][grid_y]->player != NULL) {
                Character* bomberman = (Character*) (grid[grid_x+right][grid_y]->player);
                bomberman->setAlive(false);
            }
            exp_right = new BMPSurface("textures\\explosion_right.bmp", grid[grid_x+right][grid_y]->xMin, grid[grid_x+right][grid_y]->yMin);
            exp_right->setTransparency(true, 0, 255, 0);
            screen->addComponent(exp_right, false);
            right++;
            break;
        case BOX:
            screen->deleteComponent(grid[grid_x+right][grid_y]->box);
            grid[grid_x+right][grid_y]->box = NULL;
            grid[grid_x+right][grid_y]->contain = NTHG;
            exp_right = new BMPSurface("textures\\explosion_right.bmp", grid[grid_x+right][grid_y]->xMin, grid[grid_x+right][grid_y]->yMin);
            exp_right->setTransparency(true, 0, 255, 0);
            screen->addComponent(exp_right, false);
            right++;
            break;
        default:
            break;
        }
        switch (grid[grid_x][grid_y-up]->contain)
        {
        case NTHG:
            if (grid[grid_x][grid_y-up]->player != NULL) {
                Character* bomberman = (Character*) (grid[grid_x][grid_y-up]->player);
                bomberman->setAlive(false);
            }
            exp_up = new BMPSurface("textures\\explosion_up.bmp", grid[grid_x][grid_y-up]->xMin, grid[grid_x][grid_y-up]->yMin);
            exp_up->setTransparency(true, 0, 255, 0);
            screen->addComponent(exp_up, false);
            up++;
            break;
        case BOX:
            screen->deleteComponent(grid[grid_x][grid_y-up]->box);
            grid[grid_x][grid_y-up]->box = NULL;
            grid[grid_x][grid_y-up]->contain = NTHG;
            exp_up = new BMPSurface("textures\\explosion_up.bmp", grid[grid_x][grid_y-up]->xMin, grid[grid_x][grid_y-up]->yMin);
            exp_up->setTransparency(true, 0, 255, 0);
            screen->addComponent(exp_up, false);
            up++;
            break;
        default:
            break;
        }
        switch (grid[grid_x][grid_y+down]->contain)
        {
        case NTHG:
            if (grid[grid_x][grid_y+down]->player != NULL) {
                Character* bomberman = (Character*) (grid[grid_x][grid_y+down]->player);
                bomberman->setAlive(false);
            }
            exp_down = new BMPSurface("textures\\explosion_down.bmp", grid[grid_x][grid_y+down]->xMin, grid[grid_x][grid_y+down]->yMin);
            exp_down->setTransparency(true, 0, 255, 0);
            screen->addComponent(exp_down, false);
            down++;
            break;
        case BOX:
            screen->deleteComponent(grid[grid_x][grid_y+down]->box);
            grid[grid_x][grid_y+down]->box = NULL;
            grid[grid_x][grid_y+down]->contain = NTHG;
            exp_down = new BMPSurface("textures\\explosion_down.bmp", grid[grid_x][grid_y+down]->xMin, grid[grid_x][grid_y+down]->yMin);
            exp_down->setTransparency(true, 0, 255, 0);
            screen->addComponent(exp_down, false);
            down++;
            break;
        default:
            break;
        }
        explode(left, right, up, down, i_explosion-1);
    } else SDL_Delay(1000);

    screen->deleteComponent(exp_left);
    screen->deleteComponent(exp_right);
    screen->deleteComponent(exp_up);
    screen->deleteComponent(exp_down);
    if (i_explosion == force)
        screen->deleteComponent(tmp);
}















