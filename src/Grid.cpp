#include "Grid.h"

Grid::Grid() : bmbX(1), bmbY(1)
{
    content c;
    for (int x=0; x<GRID_SIZE; x++) {
        for (int y=0; y<GRID_SIZE; y++) {
            if (x==0 || x==GRID_SIZE-1 || y==0 || y==GRID_SIZE-1 || (x%2==0 && y%2==0))
                c = WALL;
            else if (y==3 && x>0 && x<GRID_SIZE-1) c = BOX;
            else c = NTHG;
            tileTab[x][y] = new Tile({x*32, x*32+32, y*32, y*32+32}, c);
        }
    }
}

Grid::~Grid()
{}

Grid::Grid(const Grid& other)
{
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            tileTab[i][j] = new Tile(*(other.tileTab[i][j]));
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

bool Grid::collision(Character *bomberman)
{
    HITBOX htb = bomberman->getHitbox();
    switch (bomberman->getMove())
    {
    case LEFT:
        if (tileTab[bmbX-1][bmbY]->isInTile(htb) && tileTab[bmbX-1][bmbY]->getContent()!=NTHG) {
            if (tileTab[bmbX-1][bmbY]->getContent()==EXPLOSION) bomberman->kill();
            return true;
        }
        else if (tileTab[bmbX-1][bmbY-1]->isInTile(htb) && tileTab[bmbX-1][bmbY-1]->getContent()!=NTHG)
            return true;
        else if (tileTab[bmbX-1][bmbY+1]->isInTile(htb) && tileTab[bmbX-1][bmbY+1]->getContent()!=NTHG)
            return true;
        else {
            if (!tileTab[bmbX][bmbY]->isInTile(htb)) {
                tileTab[bmbX][bmbY]->setBomber(NULL);
                tileTab[bmbX-1][bmbY]->setBomber(bomberman);
                bmbX--;
            }
            return false;
        }
        break;
    case RIGHT:
        if (tileTab[bmbX+1][bmbY]->isInTile(htb) && tileTab[bmbX+1][bmbY]->getContent()!=NTHG) {
            if (tileTab[bmbX+1][bmbY]->getContent()==EXPLOSION) bomberman->kill();
            return true;
        }
        else if (tileTab[bmbX+1][bmbY-1]->isInTile(htb) && tileTab[bmbX+1][bmbY-1]->getContent()!=NTHG)
            return true;
        else if (tileTab[bmbX+1][bmbY+1]->isInTile(htb) && tileTab[bmbX+1][bmbY+1]->getContent()!=NTHG)
            return true;
        else {
            if (!tileTab[bmbX][bmbY]->isInTile(htb)) {
                tileTab[bmbX][bmbY]->setBomber(NULL);
                tileTab[bmbX+1][bmbY]->setBomber(bomberman);
                bmbX++;
            }
            return false;
        }
        break;
    case UP:
        if (tileTab[bmbX][bmbY-1]->isInTile(htb) && tileTab[bmbX][bmbY-1]->getContent()!=NTHG) {
            if (tileTab[bmbX][bmbY-1]->getContent()==EXPLOSION) bomberman->kill();
            return true;
        }
        else if (tileTab[bmbX-1][bmbY-1]->isInTile(htb) && tileTab[bmbX-1][bmbY-1]->getContent()!=NTHG)
            return true;
        else if (tileTab[bmbX+1][bmbY-1]->isInTile(htb) && tileTab[bmbX+1][bmbY-1]->getContent()!=NTHG)
            return true;
        else {
            if (!tileTab[bmbX][bmbY]->isInTile(htb)) {
                tileTab[bmbX][bmbY]->setBomber(NULL);
                tileTab[bmbX][bmbY-1]->setBomber(bomberman);
                bmbY--;
            }
            return false;
        }
        break;
    case DOWN:
        if (tileTab[bmbX][bmbY+1]->isInTile(htb) && tileTab[bmbX][bmbY+1]->getContent()!=NTHG) {
            if (tileTab[bmbX][bmbY+1]->getContent()==EXPLOSION) bomberman->kill();
            return true;
        }
        else if (tileTab[bmbX-1][bmbY+1]->isInTile(htb) && tileTab[bmbX-1][bmbY+1]->getContent()!=NTHG)
            return true;
        else if (tileTab[bmbX+1][bmbY+1]->isInTile(htb) && tileTab[bmbX+1][bmbY+1]->getContent()!=NTHG)
            return true;
        else {
            if (!tileTab[bmbX][bmbY]->isInTile(htb)) {
                tileTab[bmbX][bmbY]->setBomber(NULL);
                tileTab[bmbX][bmbY+1]->setBomber(bomberman);
                bmbY++;
            }
            return false;
        }
        break;
    default:
        return false;
        break;
    }
}

bool Grid::collision_exp(int x, int y)
{
    switch (tileTab[x][y]->getContent())
    {
    case WALL:
        return true;
        break;
    case BOX:
        tileTab[x][y]->destroy_Box();
        tileTab[x][y]->setContent(EXPLOSION);
        return false;
        break;
    case NTHG:
        tileTab[x][y]->kill_bomber();
        return false;
        break;
    default:
        return false;
    }
}














