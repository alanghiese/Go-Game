#ifndef PARTIDA_H
#define PARTIDA_H
#include "Reglas.h"
#include "Jugador.h"




class Partida
{
    public:
        ///constructora y destructora
        Partida(); ///MODIFICADO
        ~Partida();
        ///Setea el tSize dependiendo del tablero
        void setTsize(int tSize);
        ///retorna true si una jugada es posible
        bool jugadaPosible(Ficha f) ;
        ///actualiza la logica del tablero al poner la ficha f
        void actualizarTablero(Ficha f, list<Ficha> &fichasCapturadas);
        ///setea los colores de los jugadores
        void setJugadores(int colorJug1,int colorJug2);
        ///devuelve el tablero del juego
        Tablero getTablero(){return t;}
        ///copia la partida
        void copiar(Partida other);
        ///devuelve jugador 1
        Jugador getJugador1();
        ///devuelve jugador 2
        Jugador getJugador2();
        ///devuelve tablero ant
        Tablero getTableroAnt();
        ///devuelve tablero antant
        Tablero getTableroAntAnt();
        ///setea jugador 1
        void setJugador1(Jugador j1);
        ///setea jugador 2
        void setJugador2(Jugador j2);
        ///devuelve tablero
        void setTablero(Tablero t);
        ///devuelve tablero ant
        void setTableroAnt(Tablero ant);
        ///devuelve tablero antant
        void setTableroAntAnt(Tablero antant);
        ///devuelve la puntuacion actual
        void getPuntuaciones(int &j1, int &j2, int constPts, int constHuecos);



    private:
        int tSize;
        Reglas r;
        Jugador j1,j2;
        Tablero t; ///tablero actual
        Tablero tAnt;
        Tablero tAntAnt; /// tablero para el ko
};

#endif // PARTIDA_H
