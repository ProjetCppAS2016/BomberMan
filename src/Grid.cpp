#include "Grid.h"

Grid::Grid() : bmbX(1), bmbY(1)
{
    content c;
    for (int x=0; x<GRID_SIZE; x++) {
        for (int y=0; y<GRID_SIZE; y++) {
            if (x==0 || x==GRID_SIZE || y==0 || y==GRID_SIZE || (x%2==0 && y%2==0))
                c = WALL;
            else if (x==3) c = BOX;
            else c = NTHG;
            tileTab[x][y]({x*32, x*32+32, y*32, y*32+32}, c);
        }
    }
    Window::getScreen().clearScreen();
}

Grid::~Grid()
{}

Grid::Grid(const Grid& other) : bmbX(other.bmbX), bmbY(other.bmbY)
{
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            tileTab[i][j](other.tileTab[i][j]);
    }
}

Grid& Grid::operator=(const Grid& rhs)
{
    if (this == &rhs) return *this; // handle self assignment

    bmbX = rhs.bmbX;
    bmbY = rhs.bmbY;
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            tileTab[i][j] = rhs.tileTab[i][j];
    }
    return *this;
}

bool Grid::collision(Character* bomberman)
{
    HITBOX htb = bomberman->getHitbox();
    switch (bomberman->getMove())
    {
    case LEFT:
        if (tileTab[bmbX+1][bmbY].inTile(htb) && tileTab[bmbX+1][bmbY].getContent()!=NTHG)
            return true;
        else if (tileTab[bmbX+1][bmbY-1].inTile(htb) && tileTab[bmbX+1][bmbY-1].getContent()!=NTHG)
            return true;
        else if (tileTab[bmbX+1][bmbY+1].inTile(htb) && tileTab[bmbX+1][bmbY+1].getContent()!=NTHG)
            return true;
        else return false;
        break;
    case RIGHT:
        if (tileTab[bmbX-1][bmbY].inTile(htb) && tileTab[bmbX-1][bmbY].getContent()!=NTHG)
            return true;
        else if (tileTab[bmbX-1][bmbY-1].inTile(htb) && tileTab[bmbX-1][bmbY-1].getContent()!=NTHG)
            return true;
        else if (tileTab[bmbX-1][bmbY+1].inTile(htb) && tileTab[bmbX-1][bmbY+1].getContent()!=NTHG)
            return true;
        else return false;
        break;
    case Up:
        if (tileTab[bmbX][bmbY-1].inTile(htb) && tileTab[bmbX][bmbY-1].getContent()!=NTHG)
            return true;
        else if (tileTab[bmbX-1][bmbY-1].inTile(htb) && tileTab[bmbX-1][bmbY-1].getContent()!=NTHG)
            return true;
        else if (tileTab[bmbX+1][bmbY-1].inTile(htb) && tileTab[bmbX+1][bmbY-1].getContent()!=NTHG)
            return true;
        else return false;
        break;
    case DOWN:
        if (tileTab[bmbX][bmbY+1].inTile(htb) && tileTab[bmbX][bmbY+1].getContent()!=NTHG)
            return true;
        else if (tileTab[bmbX-1][bmbY+1].inTile(htb) && tileTab[bmbX-1][bmbY+1].getContent()!=NTHG)
            return true;
        else if (tileTab[bmbX+1][bmbY+1].inTile(htb) && tileTab[bmbX+1][bmbY+1].getContent()!=NTHG)
            return true;
        else return false;
        break;
    default:
        return false;
        break;
    }
}















