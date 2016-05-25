#include "Sprite.h"
#include "Screen.h"

using namespace std;

Sprite::Sprite() : Surface(), tab_img(), nbr_img(0), switch_time(0), displayed(false)
{ m_init(); }
Sprite::Sprite(int nbr, ...) : Surface(), tab_img(), nbr_img(nbr), switch_time(0), displayed(false)
{
    va_list ap;
    va_start(ap, nbr);
    for (int i=0; i<nbr; i++)
        tab_img.push_back(va_arg(ap, Surface*));
    va_end(ap);

    surface = tab_img[0]->getSurface();
    m_init();
}
Sprite::Sprite(int nbr, int time, ...) : Surface(), tab_img(), nbr_img(nbr), switch_time(time), displayed(false)
{
    va_list ap;
    va_start(ap, time);
    for (int i=0; i<nbr; i++)
        tab_img.push_back(va_arg(ap, Surface*));
    va_end(ap);

    surface = tab_img[0]->getSurface();
    m_init();
}

Sprite::~Sprite()
{
    displaySprite(false);
    pthread_mutex_destroy(m_surf);
    pthread_mutex_destroy(m_nbr);
    pthread_mutex_destroy(m_time);
    surface = NULL;
}

Sprite::Sprite(const Sprite& other) : Surface(other), tab_img(), nbr_img(other.nbr_img), switch_time(other.switch_time), displayed(false)
{
    int s = other.tab_img.size();
    for (int i=0; i<s; i++)
        tab_img.push_back(new Surface(*(other.tab_img[i])));
    m_init();
}

void Sprite::clearImgs()
{
    int s = tab_img.size();
    for (int i=0; i<s; i++)
        delete tab_img[i];
}

void Sprite::Setnbr_img(int val)
{
    pthread_mutex_lock(m_nbr);
    nbr_img = val;
    pthread_mutex_unlock(m_nbr);
}
void Sprite::setSwitch_time(int val)
{
    pthread_mutex_lock(m_time);
    switch_time = val;
    pthread_mutex_unlock(m_time);
}

void Sprite::switchSurface(int index)
{
    pthread_mutex_lock(m_surf);
    surface = tab_img[index]->getSurface();
    pthread_mutex_unlock(m_surf);
}

void* ds_thread(void *spt)
{
    Sprite *sprite = (Sprite*)spt;
    int nb = sprite->Getnbr_img(), st = sprite->getSwitch_time(), i=0;
    while (sprite->isDisplayed()) {
        sprite->switchSurface(i);
        Screen::synchronise(st);
        i++;
        if (i == nb) i=0;
    }
return NULL;
}

void Sprite::displaySprite(bool value)
{
    if (value && !displayed) {
        displayed = true;
        pthread_create(&t_disp, NULL, ds_thread, this);
    } else if (!value && displayed) {
        displayed = false;
        pthread_join(t_disp, NULL);
    }
}










