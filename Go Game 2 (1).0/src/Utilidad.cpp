#include "Utilidad.h"

Utilidad::Utilidad()
{
    //ctor
}

bool Utilidad::perteneceFichaALista(list<Ficha>listF, Ficha f) const
{
    typename list<Ficha> :: iterator it = listF.begin();
    while (it != listF.end()){
        if (f.equal(*it))
            return true;
        it++;
    }
    return false;
}



Utilidad::~Utilidad()
{
    //dtor
}
