#include "Character.h"
#include "Bomb.h"
#include "Window.h"

Character::Character() : x(0), y(0), hitbox({0,0,0,0}), gameGrid(NULL),
                         spriteLeft(NULL), spriteRight(NULL),
                         spriteUp(NULL), spriteDown(NULL), actualMove(STOP),
                         can_drop(false), alive(false)
{}

Character::Character(int x, int y, HITBOX htb, Grid *grd) :  x(x), y(y), hitbox(htb), gameGrid(grd),
                                                             spriteLeft(new Sprite(1, 90, NULL)),
                                                             spriteRight(new Sprite(1, 90, NULL)),
                                                             spriteUp(new Sprite(1, 90, NULL)),
                                                             spriteDown(new Sprite(1, 90, NULL)),
                                                             actualMove(STOP),
                                                             can_drop(true),
                                                             alive(true)
{
    string L("textures\\left_"), pathLeft, R("textures\\right_"), pathRight,
           U("textures\\up_"), pathUp, D("textures\\down_"), pathDown, bmp(".bmp");
    for (int i=1; i<7; i++) {
        pathLeft = L + intToStr(i) + bmp;
        pathRight = R + intToStr(i) + bmp;
        pathUp = U + intToStr(i) + bmp;
        pathDown = D + intToStr(i) + bmp;
        tmp = new BMPSurface(pathLeft);
        tmp->setTransparency(true, 0, 255, 0);
        spriteLeft->addImg(tmp);
        tmp = new BMPSurface(pathRight);
        tmp->setTransparency(true, 0, 255, 0);
        spriteRight->addImg(tmp);
        tmp = new BMPSurface(pathUp);
        tmp->setTransparency(true, 0, 255, 0);
        spriteUp->addImg(tmp);
        tmp = new BMPSurface(pathDown);
        tmp->setTransparency(true, 0, 255, 0);
        spriteDown->addImg(tmp);
    }
    Window::getScreen().addComponent(spriteLeft, false);
    Window::getScreen().addComponent(spriteRight, false);
    Window::getScreen().addComponent(spriteUp, false);
    Window::getScreen().addComponent(spriteDown, true);
    spriteDown->displaySprite(true);
}

Character::~Character()
{}

Character::Character(const Character& other) : x(other.x), y(other.y),
                                               hitbox(other.hitbox),
                                               gameGrid(other.gameGrid),
                                               spriteLeft(other.spriteLeft),
                                               spriteRight(other.spriteRight),
                                               spriteUp(other.spriteUp),
                                               spriteDown(other.spriteDown),
                                               actualMove(STOP),
                                               can_drop(other.can_drop),
                                               alive(other.alive)
{}

Character& Character::operator=(const Character& rhs)
{
    x = rhs.x;
    y = rhs.y;
    hitbox = rhs.hitbox;
    gameGrid = rhs.gameGrid;
    spriteLeft = rhs.spriteLeft;
    spriteRight = rhs.spriteRight;
    spriteUp = rhs.spriteUp;
    spriteDown = rhs.spriteDown;
    can_drop = rhs.can_drop;
    alive = rhs.alive;
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
            if (!gameGrid->collision(this))
                increaseX(-2);
            break;
        case RIGHT:
            if (actualMove!=RIGHT) {
                useSprite(RIGHT, 6);
                actualMove = RIGHT;
            }
            if (!gameGrid->collision(this))
                increaseX(2);
            break;
        case UP:
            if (actualMove!=UP) {
                useSprite(UP, 6);
                actualMove = UP;
            }
            if (!gameGrid->collision(this))
                increaseY(-2);
            break;
        case DOWN:
            if (actualMove!=DOWN) {
                useSprite(DOWN, 6);
                actualMove = DOWN;
            }
            if (!gameGrid->collision(this))
                increaseY(2);
            break;
        case STOP:
            if (actualMove!=STOP) useSprite(actualMove, 1);
            actualMove = STOP;
    }
}

void Character::dropBomb()
{
    if (can_drop) {
        new Bomb(grid_x, grid_y, 3, grid, this);
        can_drop = false;
    }
}

void Character::kill()
{
    alive = false;
    spriteLeft->displaySprite(false);
    spriteRight->displaySprite(false);
    spriteUp->displaySprite(false);
    spriteDown->displaySprite(false);
    BMPSurface *dead = new BMPSurface("textures\\dead.bmp", x, y);
    dead->setTransparency(true, 0, 255, 0);
    Window::getInstance().getScreen()->addComponent(dead, false);
    SDL_Delay(3000);
}











