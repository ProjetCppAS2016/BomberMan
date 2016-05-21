#include "Sprite.h"
#include "Screen.h"

using namespace std;

Sprite::Sprite() : Surface(), tab_img(), nbr_img(-1)
{ m_init(); }
Sprite::Sprite(vector<BMPSurface*> const& tab) : Surface(), tab_img(), nbr_img(-1)
{
    int s = tab.size();
    for (int i=0; i<s; i++)
        tab_img.push_back(new BMPSurface(*tab[i]));
    nbr_img = s;
    m_init();
}
Sprite::Sprite(vector<BMPSurface*> const& tab, int nbr) : Surface(), tab_img(), nbr_img(nbr)
{
    int s = tab.size();
    for (int i=0; i<s; i++)
        tab_img.push_back(new BMPSurface(*tab[i]));
    m_init();
}

Sprite::~Sprite()
{
    int s = tab_img.size();
    for (int i=0; i<s; i++)
        delete tab_img[i];
}

Sprite::Sprite(const Sprite& other) : Surface(other), tab_img(), nbr_img(other.nbr_img)
{
    int s = other.tab_img.size();
    for (int i=0; i<s; i++)
        tab_img.push_back(new BMPSurface(*(other.tab_img[i])));
    m_init();
}

void Sprite::Setnbr_img(int val)
{
    SDL_mutexP(m_nbr);
    nbr_img = val;
    SDL_mutexV(m_nbr);
}
void Sprite::setSwitch_time(int val)
{
    SDL_mutexP(m_time);
    switch_time = val;
    SDL_mutexV(m_time);
}

void Sprite::switchSurface(int index)
{
    SDL_mutexP(m_surf);
    surface = tab_img[index]->getSurface();
    SDL_mutexV(m_surf);
}

int ds_thread(void *spt)
{
    Sprite *sprite = (Sprite*)spt;
    int nb = sprite->Getnbr_img(), st = sprite->getSwitch_time(), i=0;
    while (sprite->isDisplayed()) {
        sprite->switchSurface(i);
        Screen::synchronise();
        SDL_Delay(st);
        if ((i++) == nb) i=0;
    }
return 0;
}

void Sprite::displaySprite(bool value)
{
    if (value && !displayed) {
        displayed = true;
        t_disp = SDL_CreateThread(ds_thread, this);
    } else if (!value && displayed) {
        displayed = false;
        SDL_WaitThread(t_disp, NULL);
    }
}










