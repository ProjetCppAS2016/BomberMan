#ifndef BMPSURFACE_H
#define BMPSURFACE_H

#include "Surface.h"


class BMPSurface : public Surface
{
    public:
        BMPSurface();
        void initBMP();
        BMPSurface(std::string path);
        BMPSurface(std::string path, int x, int y);
        BMPSurface(std::string path, int x, int y, int w, int h);
        virtual ~BMPSurface();
        BMPSurface(const BMPSurface& other);
        BMPSurface& operator=(const BMPSurface& rhs);

        void setBmp(std::string);
        void setTransparency(bool, Uint32);
        void setTransparency(bool, int, int, int);

    protected:

    private:
        std::string path;
};

#endif // BMPSURFACE_H
