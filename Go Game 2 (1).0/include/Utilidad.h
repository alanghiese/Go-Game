#ifndef UTILIDAD_H
#define UTILIDAD_H
#include <list>
#include "Ficha.h"
using namespace std;

class Utilidad
{
    public:
        Utilidad();
        ~Utilidad();
        bool perteneceFichaALista(list<Ficha> listF, Ficha f) const;

    protected:

    private:
};

#endif // UTILIDAD_H
