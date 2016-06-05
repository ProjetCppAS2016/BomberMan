#include "Character.h"

Character::Character() : x(0), y(0), grid_x(0), grid_y(0), spriteLeft(NULL), spriteRight(NULL), spriteUp(NULL), spriteDown(NULL), actualMove(STOP)
{
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            grid[i][j] = NULL;
    }
}

Character::Character(int g_x, int g_y, HITBOX htb,
                     Sprite* spt_L, Sprite* spt_R,
                     Sprite* spt_U,Sprite* spt_D,
                     TILE* tab[][GRID_SIZE]) : grid_x(g_x),
                                               grid_y(g_y),
                                               hitbox(htb),
                                               spriteLeft(spt_L),
                                               spriteRight(spt_R),
                                               spriteUp(spt_U),
                                               spriteDown(spt_D),
                                               actualMove(STOP)
{
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            grid[i][j] = tab[i][j];
    }
    Setx(grid[grid_x][grid_y]->xMin);
    Sety(grid[grid_x][grid_y]->yMin);
    hitbox.xMin += x;
    hitbox.xMax += x;
    hitbox.yMin += y;
    hitbox.yMax += y;
    grid[grid_x][grid_y]->player = (void*) this;
    spriteUp->displaySprite(true);
}

Character::~Character()
{}

Character::Character(const Character& other) : x(other.x), y(other.y),
                                               grid_x(other.grid_x),
                                               grid_y(other.grid_y),
                                               hitbox(other.hitbox),
                                               spriteLeft(other.spriteLeft),
                                               spriteRight(other.spriteRight),
                                               spriteUp(other.spriteUp),
                                               spriteDown(other.spriteDown),
                                               actualMove(STOP)
{
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            grid[i][j] = other.grid[i][j];
    }
    grid[grid_x][grid_y]->player = (void*) this;
}

Character& Character::operator=(const Character& rhs)
{
    x = rhs.x;
    y = rhs.y;
    hitbox = rhs.hitbox;
    grid_x = rhs.grid_x;
    grid_y = rhs.grid_y;
    spriteLeft = rhs.spriteLeft;
    spriteRight = rhs.spriteRight;
    spriteUp = rhs.spriteUp;
    spriteDown = rhs.spriteDown;
    return *this;
}

void Character::Setx(int val)
{
    x = val;
    spriteLeft->Setx(x);
    spriteRight->Setx(x);
    spriteUp->Setx(x);
    spriteDown->Setx(x);
}
void Character::Sety(int val)
{
    y = val;
    spriteLeft->Sety(y);
    spriteRight->Sety(y);
    spriteUp->Sety(y);
    spriteDown->Sety(y);
}

void Character::increaseX(int amount)
{
    Setx(x+amount);
    hitbox.xMin += amount;
    hitbox.xMax += amount;
}

void Character::increaseY(int amount)
{
    Sety(y+amount);
    hitbox.yMin += amount;
    hitbox.yMax += amount;
}

void Character::useSprite(moves direction, int nbrImg)
{
    if (spriteLeft->isDisplayed()) spriteLeft->displaySprite(false);
    else if(spriteRight->isDisplayed()) spriteRight->displaySprite(false);
    else if (spriteUp->isDisplayed()) spriteUp->displaySprite(false);
    else if (spriteDown->isDisplayed()) spriteDown->displaySprite(false);

    switch (direction)
    {
        case LEFT:
                spriteLeft->Setnbr_img(nbrImg);
                spriteLeft->displaySprite(true);
            break;
        case RIGHT:
                spriteRight->Setnbr_img(nbrImg);
                spriteRight->displaySprite(true);
            break;
        case UP:
                spriteUp->Setnbr_img(nbrImg);
                spriteUp->displaySprite(true);
            break;
        case DOWN:
                spriteDown->Setnbr_img(nbrImg);
                spriteDown->displaySprite(true);
            break;
        default:
            break;
    }
}

void Character::moveTo(moves direction)
{
    switch (direction)
    {
        case LEFT:
            if (actualMove!=LEFT) {
                useSprite(LEFT, 6);
                actualMove = LEFT;
            }
            if (hitbox.xMin > grid[grid_x][grid_y]->xMin) {
                increaseX(-2);
                if (hitbox.xMax <= grid[grid_x][grid_y]->xMax)
                    grid[grid_x+1][grid_y]->player = NULL;
            } else if (grid[grid_x-1][grid_y]->contain==NTHG) {
                grid_x--;
                grid[grid_x][grid_y]->player = (void*) this;
                increaseX(-2);
            }
            break;
        case RIGHT:
            if (actualMove!=RIGHT) {
                useSprite(RIGHT, 6);
                actualMove = RIGHT;
            }
            if (hitbox.xMax+2 < grid[grid_x][grid_y]->xMax) {
                increaseX(2);
                if (hitbox.xMin >= grid[grid_x][grid_y]->xMin)
                    grid[grid_x-1][grid_y]->player = NULL;
            } else if (grid[grid_x+1][grid_y]->contain==NTHG) {
                grid_x++;
                grid[grid_x][grid_y]->player = (void*) this;
                increaseX(2);
            }
            break;
        case UP:
            if (actualMove!=UP) {
                useSprite(UP, 6);
                actualMove = UP;
            }
            if (hitbox.yMin-2 > grid[grid_x][grid_y]->yMin) {
                increaseY(-2);
                if (hitbox.yMax<=grid[grid_x][grid_y]->yMax)
                    grid[grid_x][grid_y+1]->player = NULL;
            } else if (grid[grid_x][grid_y-1]->contain==NTHG) {
                grid_y--;
                grid[grid_x][grid_y]->player = (void*) this;
                increaseY(-2);
            }
            break;
        case DOWN:
            if (actualMove!=DOWN) {
                useSprite(DOWN, 6);
                actualMove = DOWN;
            }
            if (hitbox.yMax+2 < grid[grid_x][grid_y]->yMax) {
                increaseY(2);
                if (hitbox.yMin >= grid[grid_x][grid_y]->yMin)
                    grid[grid_x][grid_y-1]->player = NULL;
            } else if (grid[grid_x][grid_y+1]->contain==NTHG) {
                grid_y++;
                grid[grid_x][grid_y]->player = (void*) this;
                increaseY(2);
            }
            break;
        case STOP:
            if (actualMove!=STOP) useSprite(actualMove, 1);
            actualMove = STOP;
    }
}











