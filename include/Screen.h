#ifndef SCREEN_H
#define SCREEN_H
#include "Surface.h"

class Screen : public Surface
{
    public:
        Screen();
        Screen(SDL_Surface*);
        ~Screen();
        Screen(const Screen& other);

        void setBgColor(int, int, int);
        void addComponent(Surface&);
        void refresh();

    protected:

    private:

};

#endif // SCREEN_H
