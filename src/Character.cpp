#include "Character.h"

using namespace std;

string intToStr(int i)
{
    std::ostringstream stream;
    stream << i;
    return stream.str();
}

Character::Character() : x(0), y(0), hitbox({0,0,0,0}),
                         spriteLeft(NULL), spriteRight(NULL),
                         spriteUp(NULL), spriteDown(NULL), actualMove(STOP),
                         can_drop(false), alive(false)
{}

Character::Character(int X, int Y, HITBOX htb) : x(0), y(0), hitbox(htb),
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
   BMPSurface *tmp;
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
    Window::getScreen().addComponent(spriteDown, false);
    increaseX(X);
    increaseY(Y);

    useSprite(DOWN, 1);
}

Character::~Character()
{
    Window::getScreen().deleteComponent(spriteLeft);
    Window::getScreen().deleteComponent(spriteRight);
    Window::getScreen().deleteComponent(spriteUp);
    Window::getScreen().deleteComponent(spriteDown);
}

Character::Character(const Character& other) : x(other.x), y(other.y),
                                               hitbox(other.hitbox),
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

void Character::kill()
{
    alive = false;
    spriteLeft->displaySprite(false);
    spriteRight->displaySprite(false);
    spriteUp->displaySprite(false);
    spriteDown->displaySprite(false);
    BMPSurface *dead = new BMPSurface("textures\\dead.bmp", x, y);
    dead->setTransparency(true, 0, 255, 0);
    Window::getScreen().addComponent(dead, false);
}











