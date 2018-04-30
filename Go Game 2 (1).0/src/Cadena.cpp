#include "Cadena.h"

Cadena::Cadena(int tSize){
    this->tSize = tSize;

    misFichas = new bool * [tSize];
    for (int i = 0; i < tSize; i++)
        misFichas[i] = new bool[tSize];

    for (int i = 0; i < tSize; i++)
        for (int j = 0; j < tSize; j++)
            misFichas[i][j] = false;
}

Cadena::Cadena(int tSize,list<Ficha> lf,bool** m)
{
    this->tSize = tSize;

    misFichas = new bool * [tSize];
    for (int i = 0; i < tSize; i++)
        misFichas[i] = new bool[tSize];

    for (int i = 0; i < tSize; i++)
        for (int j = 0; j < tSize; j++)
            misFichas[i][j] = false;

    fichas = lf;
    misFichas = m;
}

bool** Cadena::getMatriz()
{
    bool **m;
    m = new bool * [tSize];
    for (int i = 0; i < tSize; i++)
        m[i] = new bool[tSize];

    for (int i = 0; i < tSize; i++)
        for (int j = 0; j < tSize; j++)
            m[i][j] = misFichas[i][j];
    return m;
}

list<Ficha> Cadena::getFichas()
{
    list<Ficha> l;
    typename list<Ficha> :: const_iterator it = fichas.begin();
    while (it != fichas.end()){
        Ficha f(it->getFila(),it->getColumna(),it->getColor());
        l.push_back(f);
        it++;
    }
    return l;
}

list<Ficha> Cadena::getFichas() const
{
    return fichas;
}

bool Cadena::equal(Cadena other) const
{
    Utilidad util;
    typename list<Ficha> :: const_iterator it = fichas.begin();
    while (it != fichas.end()){
        if (!util.perteneceFichaALista(other.getFichas(),*it))
            return false;
        it++;
    }
    return true;
}

bool Cadena::operator==(Cadena other) const
{
    return equal(other);
}


void Cadena::addFicha(Ficha f)
{
    fichas.push_back(f);
    misFichas[f.getFila()][f.getColumna()] = true;
}

bool Cadena::pertenece(Ficha f) const
{
    return misFichas[f.getFila()][f.getColumna()];
}



Cadena::~Cadena()
{
    //dtor
}
