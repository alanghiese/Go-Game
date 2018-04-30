#ifndef HEURISTICA_H
#define HEURISTICA_H
#include <Partida.h>


class Heuristica
{
    public:
        ///constructoras y destructor
        Heuristica(int constPts, int constHuecos, int tSize);
        Heuristica(){};
        ~Heuristica();
        ///obtener el valor de la heurista para un jugador en una partida
        int getValorHeuristico(Partida p, int color);
        int getValorHeuristicoRelativo(Partida p, int color);


    private:
        bool miHueco(int ** c, int fila, int columna, int color);
        Reglas r;
        int constPts;
        int constFichasPuestas;
        int constCercos;
        int constHuecos;
        int tSize;
};

#endif // HEURISTICA_H
