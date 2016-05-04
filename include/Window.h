#ifndef WINDOW_H
#define WINDOW_H
#include <SDL/SDL.h>
#include <iostream>
#include <vector>
#include "Surface.h"

class Window
{
    public:
        Window(int, int, int);
        Window(int, int, int, std::string);
        virtual ~Window();
        Window(const Window& other);

        int getWidth();
        int getHeight();
        int getDepth();
        void setTitle(std::string);
        std::string getTitle();

        void WaitEvent(Uint8);
        void setBgColor(int, int, int);
        void addComponent(Surface*);

    protected:

    private:
        int width;
        int height;
        int depth;
        Surface* screen;
        std::string title;
        std::vector<Surface*> content;
};

#endif // WINDOW_H
