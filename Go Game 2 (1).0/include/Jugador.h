#ifndef JUGADOR_H
#define JUGADOR_H
#include "CajaDeFichas.h"
#include "list"

class Jugador
{
    public:
        ///constructoras y destructor
        Jugador();
        ~Jugador();

        ///setea el color del jugador
        void setColor(int color);
        ///devuelve la cantidad de fichas disponibles
        int getCantDisp() const;
        ///devuelve el color del jugador
        int getColor() const ;
        ///devuelve la caja de fichas del jugador
        CajaDeFichas getCajaDeFichas() ;
        ///setea caja de fichas
        void setCajaDeFichas(CajaDeFichas caja);
        ///obtiene los puntos actuales del jugador
        int getPts();
        ///copiar jugador
        void copiar(Jugador other);
        /// le suma x pts a los actuales
        void addPts(int x);


    private:
        CajaDeFichas caja;
        int pts;
};

#endif // JUGADOR_H
