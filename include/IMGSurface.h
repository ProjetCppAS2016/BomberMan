#ifndef IMGSURFACE_H
#define IMGSURFACE_H

#include "Surface.h"
#include <SDL\SDL_image.h>


class IMGSurface : public Surface
{
    public:
        IMGSurface();
        void initIMG();
        IMGSurface(std::string);
        IMGSurface(std::string, int, int);
        IMGSurface(std::string, int, int, int, int);
        virtual ~IMGSurface();
        IMGSurface(const IMGSurface& other);

        void setImg(std::string);

    protected:

    private:
        std::string path;
};

#endif // IMGSURFACE_H
