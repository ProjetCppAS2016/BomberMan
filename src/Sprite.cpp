#include "Sprite.h"
#include "Screen.h"

using namespace std;

void Sprite::m_init()
{
    m_surf = new(pthread_mutex_t);
    m_nbr = new(pthread_mutex_t);
    m_time = new(pthread_mutex_t);
    pthread_mutex_init(m_surf, NULL);
    pthread_mutex_init(m_nbr, NULL);
    pthread_mutex_init(m_time, NULL);
}

Sprite::Sprite() : Surface(), tab_img(), nbr_img(0), switch_time(0), displayed(false)
{ m_init(); }

Sprite::Sprite(int nbr, ...) : Surface(), tab_img(), nbr_img(nbr), switch_time(0), displayed(false)
{
    int i=-1;
    Surface *tmp;
    va_list ap;
    va_start(ap, nbr);
    while(((i++)<nbr) && ((tmp=va_arg(ap, Surface*))!=NULL))
        tab_img.push_back(tmp);
    va_end(ap);

    m_init();
}
Sprite::Sprite(int nbr, int time, ...) : Surface(), tab_img(), nbr_img(nbr), switch_time(time), displayed(false)
{
    int i=-1;
    Surface *tmp;
    va_list ap;
    va_start(ap, time);
    while(((i++)<nbr) && ((tmp=va_arg(ap, Surface*))!=NULL))
        tab_img.push_back(tmp);
    va_end(ap);

    m_init();
}

Sprite::~Sprite()
{
    displaySprite(false);
    pthread_mutex_destroy(m_surf);
    pthread_mutex_destroy(m_nbr);
    pthread_mutex_destroy(m_time);
}

Sprite::Sprite(const Sprite& other) : Surface(other), tab_img(), nbr_img(other.nbr_img), switch_time(other.switch_time), displayed(false)
{
    int s = other.tab_img.size();
    for (int i=0; i<s; i++)
        tab_img.push_back(new Surface(*(other.tab_img[i])));
    m_init();
}

Sprite& Sprite::operator=(const Sprite& rhs)
{
    if (this == &rhs) return *this;

    int s_rhs = rhs.tab_img.size(), s_this = tab_img.size();
    if (s_rhs < s_this) {
        for (int i=0; i<s_this-s_rhs; i++)
            tab_img.push_back(NULL);
    }
    if (s_rhs > s_this) {
        for (int i=0; i<s_rhs-s_this; i++)
            tab_img.pop_back();
    }
    for (int i=0; i<s_rhs; i++)
        *tab_img[i] = *(rhs.tab_img[i]);

    nbr_img = rhs.nbr_img;
    switch_time = rhs.switch_time;
    displayed = false;
    *m_surf = *(rhs.m_surf);
    *m_nbr = *(rhs.m_nbr);
    *m_time = *(rhs.m_time);
    t_disp = rhs.t_disp;
    return *this;
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
        surface = NULL;
    }
}










