#ifndef SCREEN_H
#define SCREEN_H
#include <vector>
#include <pthread.h>
#include "Surface.h"
#include "Structures.h"


class Screen : public Surface
{
    public:
        Screen();
        Screen(SDL_Surface* surface);
        virtual ~Screen();
        Screen(const Screen& other);

        void setBgColor(int red, int green, int blue);
        void setFps(int f) { fps = (1000-(1000%f))/f; }
        int getFps() { return fps; }
        bool hasAuto_refresh() { return auto_refresh; }

        virtual void addComponent(Surface& component);
        virtual void addStaticComponent(Surface& component);
        void deleteComponent(Surface* component);
        void deleteStaticComponent();
        void deleteAllComponents();
        void refresh();
        void refreshAll();
        void clearScreen();
        void activateA_R(bool value);
        static void synchronise(int delay);
        static void lockSync();
        static void unlockSync();
        static void broadcastSync() { pthread_cond_broadcast(synchronization->c_sync); }

    protected:

    private:
        static SYNC *synchronization;

        Uint32 bgColor;
        COMPONENT* listComponents;
        std::vector<Surface*> listStaticsComponents;
        bool auto_refresh;
        pthread_t thread_ar;
        MUTEX *scr_mutexes;
        int fps;

        void t_init()
        {
            scr_mutexes = new(MUTEX);
            scr_mutexes->m_components = new (pthread_mutex_t);
            scr_mutexes->m_screen = new (pthread_mutex_t);
            synchronization->m_sync = new (pthread_mutex_t);
            synchronization->c_sync = new (pthread_cond_t);
            pthread_mutex_init(scr_mutexes->m_components, NULL);
            pthread_mutex_init(scr_mutexes->m_screen, NULL);
            pthread_mutex_init(synchronization->m_sync, NULL);
            pthread_cond_init(synchronization->c_sync, NULL);
            synchronization->cond_locked = synchronization->locked = false;
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

                blit(*(t->object));
            }
        }
};

#endif // SCREEN_H








