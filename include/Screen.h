#ifndef SCREEN_H
#define SCREEN_H
#include "Surface.h"
#include <vector>


class Screen : public Surface
{
    public:
        Screen();
        Screen(SDL_Surface*);
        ~Screen();
        Screen(const Screen& other);

        void setBgColor(int, int, int);
        Surface& getComponent(int);

        virtual void addComponent(Surface&);
        virtual void addStaticComponent(Surface&);
        void deleteComponent(Surface*);
        void deleteStaticComponent();
        void deleteAllCompenents();
        void refresh();
        void refreshAll();
        void clearScreen();

    protected:

    private:
        Uint32 bgColor;

        typedef struct COMPONENT {COMPONENT* prev;
                                  COMPONENT* next;
                                  Surface *object;} COMPONENT;
        COMPONENT* listComponents;
        std::vector<Surface*> listStaticsComponents;

        void blit(Surface& component)
        {
            SDL_Rect position;
            position.x = component.Getx();
            position.y = component.Gety();
            if (component.getDisp_h()!=-1)
                position.h = component.getDisp_h();
            if (component.getDisp_w()!=-1)
                position.w = component.getDisp_w();

            SDL_BlitSurface(component.getSurface(), NULL, surface, &position);
        }
        void delall(COMPONENT *t)
        {
            if (t->next!=NULL) delall(t->next);

            SDL_Surface *tmp_s = new SDL_Surface;
            *tmp_s = *(t->object->getSurface());
            SDL_FreeSurface(t->object->getSurface());
            t->object->setSurface(tmp_s);
            delete t;
        }
        void refscr(COMPONENT *t)
        {
            if (t->next!=NULL) refscr(t->next);

            if (t->object->isModified()) {
                blit(*(t->object));
                t->object->setModified(false);
            }
        }
};

#endif // SCREEN_H








