#ifndef CADENA_H
#define CADENA_H
#include "Utilidad.h"


class Cadena
{
    public:
        Cadena(int tSize);
        Cadena(int tSize,list<Ficha> lf,bool** m);
        ~Cadena();
        void addFicha(Ficha f);
        list<Ficha> getFichas() const;
        bool pertenece(Ficha f) const;
        bool equal(Cadena other) const;
        bool operator ==(Cadena other) const;
        list<Ficha> getFichas();
        bool** getMatriz();
    private:
        int tSize;
        list<Ficha> fichas;
        bool **misFichas;
};

#endif // CADENA_H
