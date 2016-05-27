#ifndef BMPSURFACE_H
#define BMPSURFACE_H

#include "Surface.h"


class BMPSurface : public Surface
{
    public:
        BMPSurface();
        void initBMP();
        BMPSurface(std::string);
        BMPSurface(std::string, int, int);
        BMPSurface(std::string, int, int, int, int);
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
