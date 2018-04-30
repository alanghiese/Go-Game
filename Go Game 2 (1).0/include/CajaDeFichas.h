#ifndef CAJADEFICHAS_H
#define CAJADEFICHAS_H
#include <list>
#include "Ficha.h"
#include <iostream>
using namespace std;

class CajaDeFichas
{
    public:
        ///constructoras y destructor
        CajaDeFichas(int color);
        CajaDeFichas();
        void assign(int color);
        ~CajaDeFichas();

        ///cantidad de fichas disponibles en la caja
        int getDisponibles() const ;
        ///devuelve el color de las fichas de la caja
        int getColor() const ;
        ///setea color
        void setColor(int color);
        ///agrega una ficha a las usadas
        void usarFicha() ;
        ///copiar caja
        void copiar(CajaDeFichas other);

    private:
        int disponibles;
        int color;
};

#endif // CAJADEFICHAS_H
