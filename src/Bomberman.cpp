#include "Bomberman.h"

Bomberman::Bomberman() : Character()
{}

Bomberman::Bomberman(int x, int y, HITBOX htb, Grid *gameGrid) : Character(x, y, htb),
                                                                 gameGrid(gameGrid)
{}

Bomberman::~Bomberman()
{}

Bomberman::Bomberman(const Bomberman& other) : Character(other), gameGrid(other.gameGrid)
{}

void Bomberman::moveTo(moves direction)
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

void Bomberman::waitEvents()
{
    SDL_EnableKeyRepeat(5, 5);
    SDL_Event event;
    Screen& mainScreen = Window::getScreen();
    bool flag = true;

    while (flag) {

        SDL_WaitEvent(&event);

        if (!alive) flag = false;
        switch (event.type) {
        case SDL_QUIT:
            alive = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                    moveTo(LEFT);
                    mainScreen.synchronise(20);
                break;
            case SDLK_RIGHT:
                    moveTo(RIGHT);
                    mainScreen.synchronise(20);
                break;
            case SDLK_UP:
                    moveTo(UP);
                    mainScreen.synchronise(20);
                break;
            case SDLK_DOWN:
                    moveTo(DOWN);
                    mainScreen.synchronise(20);
                break;
            case SDLK_SPACE:
                    if (!can_drop && SDL_GetTicks()-time_drop>=4600) can_drop = true;
                    dropBomb();
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            moveTo(STOP);
        }
    }
    if (!alive) SDL_Delay(1000);
}

void Bomberman::dropBomb()
{
    if (can_drop) {
        time_drop = SDL_GetTicks();
        new Bomb(gameGrid->getBmbX(), gameGrid->getBmbY(), gameGrid);
        can_drop = false;
    }
}
















