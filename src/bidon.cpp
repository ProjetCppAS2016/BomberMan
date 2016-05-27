#include "bidon.h"

bidon::bidon()
{
    //ctor
}

bidon::~bidon()
{
    //dtor
}

bidon& bidon::operator=(const bidon& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
