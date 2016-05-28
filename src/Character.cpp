#include "Character.h"

Character::Character() : x(0), y(0), grid_x(0), grid_y(0), charSprite()
{
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            grid[i][j] = NULL;
    }
}

Character::Character(int x, int y, int g_x, int g_y,
                     Sprite* spt_L, Sprite* spt_R,
                     Sprite* spt_U,Sprite* spt_D,
                     TILE* tab[][GRID_SIZE]) : x(x), y(y),
                                               grid_x(g_x),
                                               grid_y(g_y),
                                               spriteLeft(spt_L),
                                               spriteRight(spt_R),
                                               spriteUp(spt_U),
                                               spriteDown(spt_D)
{
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            grid[i][j] = tab[i][j];
    }
    charSprite.displaySprite(true);
}

Character::~Character()
{}

Character::Character(const Character& other) : x(other.x), y(other.y),
                                               grid_x(other.grid_x),
                                               grid_y(other.grid_y),
                                               spriteLeft(other.spt_L),
                                               spriteRight(other.spt_R),
                                               spriteUp(other.spt_U),
                                               spriteDown(other.spt_D)
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
    grid_x = rhs.grid_x;
    grid_y = rhs.grid_y;
    charSprite = rhs.charSprite;
    return *this;
}

void Character::deplacer(moves direction)
{
    switch (direction)
    {
        case LEFT:
            if (x-1 > grid[grid_x][grid_y]->xMin)
                x--;
            else if (grid[grid_x-1][grid_y]->contain==NTHG) {
                grid_x--;
                x--;
            }
            break;
        case RIGHT:
            if (x+sizeX+1 > grid[grid_x][grid_y]->xMax)
                x++;
            else if (grid[grid_x+1][grid_y]->contain==NTHG) {
                grid_x++;
                x++;
            }
            break;
        case UP:
            if (y-1 > grid[grid_x][grid_y]->yMin)
                y--;
            else if (grid[grid_x][grid_y-1]->contain==NTHG) {
                grid_y--;
                y--;
            }
            break;
        case DOWN:
            if (y+sizeY+1 > grid[grid_x][grid_y]->yMax)
                y++;
            else if (grid[grid_x][grid_y+1]->contain==NTHG) {
                grid_y++;
                y++;
            }
    }
}











