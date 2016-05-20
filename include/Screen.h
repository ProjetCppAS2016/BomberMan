#ifndef SCREEN_H
#define SCREEN_H
#include "Surface.h"
#include "Structures.h"
#include <vector>


class Screen : public Surface
{
    public:
        Screen();
        Screen(SDL_Surface* surface);
        ~Screen();
        Screen(const Screen& other);

        void setBgColor(int red, int green, int blue);
        void setFps(int f) { fps = f; }
        int getFps() { return fps; }


        virtual void addComponent(Surface& component);
        virtual void addStaticComponent(Surface& component);
        void deleteComponent(Surface* component);
        void deleteStaticComponent();
        void deleteAllCompenents();
        void refresh();
        void refreshAll();
        void clearScreen();
        void setAuto_refresh(bool activated);
        void auto_ref();

    protected:

    private:
        Uint32 bgColor;
        COMPONENT* listComponents;
        std::vector<Surface*> listStaticsComponents;
        bool auto_refresh;
        SDL_Thread *thread_ar;
        MUTEX *scr_mutexes;
        int fps;

        void m_init()
        {
            scr_mutexes = new(MUTEX);
            scr_mutexes->m_components = SDL_CreateMutex();
            scr_mutexes->m_screen = SDL_CreateMutex();
        }
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
            if (t!=NULL) {
                if (t->next!=NULL) refscr(t->next);

                if (t->object->isModified()) {
                    blit(*(t->object));
                    t->object->setModified(false);
                }
            }
        }
};

#endif // SCREEN_H








