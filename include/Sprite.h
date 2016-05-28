#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <cstdarg>
#include <pthread.h>
#include "Surface.h"
#include "Structures.h"


class Sprite : public Surface
{
    public:
        Sprite();
        Sprite(int nbr, ...);
        Sprite(int nbr, int time, ...);
        virtual ~Sprite();
        Sprite(const Sprite& other);
        Sprite& operator=(const Sprite& rhs);

        int Getnbr_img() { return nbr_img; }
        void Setnbr_img(int val);
        int getSwitch_time() { return switch_time; }
        void setSwitch_time(int val);
        bool isDisplayed() { return displayed; }

        void displaySprite(bool value);
        void switchSurface(int index);
        void addImg(Surface* img) { tab_img.push_back(img); }
        void clearImgs();

    protected:

    private:
        std::vector<Surface*> tab_img;
        int nbr_img;
        int switch_time;
        bool displayed;
        pthread_mutex_t *m_surf;
        pthread_mutex_t *m_nbr;
        pthread_mutex_t *m_time;
        pthread_t t_disp;

        void m_init();
};

#endif // SPRITE_H







