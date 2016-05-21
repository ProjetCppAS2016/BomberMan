#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include "Surface.h"
#include "BMPSurface.h"
#include "Structures.h"


class Sprite : public Surface
{
    public:
        Sprite();
        Sprite(std::vector<BMPSurface*> const& tab);
        Sprite(std::vector<BMPSurface*> const& tab, int nbr);
        virtual ~Sprite();
        Sprite(const Sprite& other);

        int Getnbr_img() { return nbr_img; }
        void Setnbr_img(int val);
        int getSwitch_time() { return switch_time; }
        void setSwitch_time(int val);
        bool isDisplayed() { return displayed; }

        void displaySprite(bool value);
        void switchSurface(int index);

    protected:

    private:
        std::vector<BMPSurface*> tab_img;
        int nbr_img;
        int switch_time;
        bool displayed;
        SDL_mutex *m_surf;
        SDL_mutex *m_nbr;
        SDL_mutex *m_time;
        SDL_Thread *t_disp;

        void m_init()
        {
            m_surf = SDL_CreateMutex();
            m_nbr = SDL_CreateMutex();
            m_time = SDL_CreateMutex();
        }
};

#endif // SPRITE_H







