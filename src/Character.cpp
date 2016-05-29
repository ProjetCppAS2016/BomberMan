#include "Character.h"

Character::Character() : x(0), y(0), grid_x(0), grid_y(0), sizeX(0), sizeY(0), spriteLeft(NULL), spriteRight(NULL), spriteUp(NULL), spriteDown(NULL)
{
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            grid[i][j] = NULL;
    }
}

Character::Character(int g_x, int g_y, int sX, int sY,
                     Sprite* spt_L, Sprite* spt_R,
                     Sprite* spt_U,Sprite* spt_D,
                     TILE* tab[][GRID_SIZE]) : grid_x(g_x),
                                               grid_y(g_y),
                                               sizeX(sX),
                                               sizeY(sY),
                                               spriteLeft(spt_L),
                                               spriteRight(spt_R),
                                               spriteUp(spt_U),
                                               spriteDown(spt_D)
{
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            grid[i][j] = tab[i][j];
    }
    Setx(grid[grid_x][grid_y]->xMin);
    Sety(grid[grid_x][grid_y]->yMin);
    spriteUp->displaySprite(true);
}

Character::~Character()
{}

Character::Character(const Character& other) : x(other.x), y(other.y),
                                               grid_x(other.grid_x),
                                               grid_y(other.grid_y),
                                               sizeX(other.sizeX),
                                               sizeY(other.sizeY),
                                               spriteLeft(other.spriteLeft),
                                               spriteRight(other.spriteRight),
                                               spriteUp(other.spriteUp),
                                               spriteDown(other.spriteDown)
{
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            grid[i][j] = other.grid[i][j];
    }
}

Character& Character::operator=(const Character& rhs)
{
    x = rhs.x;
    y = rhs.y;
    sizeX = rhs.sizeX;
    sizeY = rhs.sizeY;
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

void Character::useSprite(moves direction, int nbrImg)
{
    switch (direction)
    {
        case LEFT:
            if (!spriteLeft->isDisplayed()) {
                if (spriteRight->isDisplayed()) spriteRight->displaySprite(false);
                else if (spriteUp->isDisplayed()) spriteUp->displaySprite(false);
                else if (spriteDown->isDisplayed()) spriteDown->displaySprite(false);
                spriteLeft->Setnbr_img(nbrImg);
                spriteLeft->displaySprite(true);
            }
            break;
        case RIGHT:
            if (!spriteRight->isDisplayed()) {
                if (spriteLeft->isDisplayed()) spriteLeft->displaySprite(false);
                else if (spriteUp->isDisplayed()) spriteUp->displaySprite(false);
                else if (spriteDown->isDisplayed()) spriteDown->displaySprite(false);
                spriteRight->Setnbr_img(nbrImg);
                spriteRight->displaySprite(true);
            }
            break;
        case UP:
            if (!spriteUp->isDisplayed()) {
                if (spriteLeft->isDisplayed()) spriteLeft->displaySprite(false);
                else if (spriteRight->isDisplayed()) spriteRight->displaySprite(false);
                else if (spriteDown->isDisplayed()) spriteDown->displaySprite(false);
                spriteUp->Setnbr_img(nbrImg);
                spriteUp->displaySprite(true);
            }
            break;
        case DOWN:
            if (!spriteDown->isDisplayed()) {
                if (spriteLeft->isDisplayed()) spriteLeft->displaySprite(false);
                else if (spriteRight->isDisplayed()) spriteRight->displaySprite(false);
                else if (spriteUp->isDisplayed()) spriteUp->displaySprite(false);
                spriteDown->Setnbr_img(nbrImg);
                spriteDown->displaySprite(true);
            }
    }
}

void Character::moveTo(moves direction)
{
    switch (direction)
    {
        case LEFT:
            if (x-1 > grid[grid_x][grid_y]->xMin)
                Setx(x-1);
            else if (grid[grid_x-1][grid_y]->contain==NTHG) {
                if (x+sizeX <= grid[grid_x-1][grid_y]->xMax) grid_x--;
                Setx(x-1);
            }
            useSprite(LEFT, 6);
            break;
        case RIGHT:
            if (x+sizeX+1 < grid[grid_x][grid_y]->xMax)
                Setx(x+1);
            else if (grid[grid_x+1][grid_y]->contain==NTHG) {
                if (x >= grid[grid_x+1][grid_y]->xMin) grid_x++;
                Setx(x+1);
            }
            useSprite(RIGHT, 6);
            break;
        case UP:
            if (y-1 > grid[grid_x][grid_y]->yMin)
                Sety(y-1);
            else if (grid[grid_x][grid_y-1]->contain==NTHG) {
                if (y+sizeY <= grid[grid_x][grid_y-1]->yMax) grid_y--;
                Sety(y-1);
            }
            useSprite(UP, 6);
            break;
        case DOWN:
            if (y+sizeY+1 < grid[grid_x][grid_y]->yMax)
                Sety(y+1);
            else if (grid[grid_x][grid_y+1]->contain==NTHG) {
                if (y >= grid[grid_x][grid_y+1]->yMin) grid_y++;
                Sety(y+1);
            }
            useSprite(DOWN, 6);
    }
}











