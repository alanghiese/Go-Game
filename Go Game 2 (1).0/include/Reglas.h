#ifndef REGLAS_H
#define REGLAS_H
#include "Tablero.h"

class Reglas
{
    public:
        ///constructora y destructora
        Reglas();
        ~Reglas();

        ///devuelven true si son KO,ojo, suicidio
        bool KO(Ficha f, Tablero t, Tablero estAnt) const;
        bool ojo(Ficha f, Tablero t) const;
        bool suicidio(Ficha f, Tablero t) const;
        ///devuelve true si es una jugada valida
        bool comprobar(Ficha f, Tablero t, Tablero estAnt) const;
        void setTSize(int t){this->tSize = t;}

    private:
        ///funcion que retorna la cadena de una ficha
        void getHijos(Ficha f,Tablero t,list<Ficha> &hijos, Ficha o) const;
        ///devuelve la cantidad de huecos alrededor de una ficha
        bool cantHuecos(Ficha f, Tablero t, int maximo) const;
        int tSize;
};

#endif // REGLAS_H
