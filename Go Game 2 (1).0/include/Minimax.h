#ifndef MINIMAX_H
#define MINIMAX_H
#include "Heuristica.h"

class Minimax
{
    public:
        Minimax();
        ~Minimax();
        ///obtener la mejor ficha segun la heuristica utilizando el algoritmo minimax
        Ficha nextPlay(Partida p) ;
        ///setea los valores del minimax
        void setValores(Heuristica Heu, Reglas r);

    private:

        struct dupla{
            int valor;
            Ficha ficha;
        };

        ///algoritmo minimax privado
        dupla minimax(Partida p, int nivel, int jug);
        ///retorna true si un estado del tablero es hoja (estado final)
        bool esHoja(Tablero t) const;
        dupla minimo(list<dupla> l);
        dupla maximo(list<dupla> l);
        void getHijos(list<dupla>& ld, Partida p, int Jugador);


        Heuristica heuristica;
        Reglas r;

};

#endif // MINIMAX_H
