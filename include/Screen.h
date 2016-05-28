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
        Screen (const Surface& other);

        Screen& operator=(const Surface&);
        void setBgColor(int red, int green, int blue);
        void setFps(int f) { fps = (1000-(1000%f))/f; }
        int getFps() { return fps; }
        bool hasAuto_refresh() { return auto_refresh; }

        void addComponent(Surface *component, bool refresh);
        void addStaticComponent(Surface *component, bool refresh);
        void deleteComponent(Surface *component);
        void deleteStaticComponent(bool refresh);
        void deleteAllComponents();
        void refresh();
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

        void t_init();
        void blit(Surface& component);
        void delall(COMPONENT *t);
        void refscr(COMPONENT *t);
};

#endif // SCREEN_H








