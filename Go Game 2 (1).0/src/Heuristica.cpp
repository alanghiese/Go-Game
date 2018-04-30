#include "Heuristica.h"


Heuristica::Heuristica(int constPts, int constHuecos, int tSize){
        this->constPts = constPts;
        this->constHuecos = constHuecos;
        this->tSize = tSize;
        r.setTSize(tSize);
}

bool Heuristica::miHueco(int ** c, int fila, int columna, int color){

    int cero = 0;
    int uno = 0;
    if(c[fila][columna] == color)
        return true;

    if (fila-1 >= 0){
        if (c[fila-1][columna] == 0 && c[fila][columna] == -1) cero++;
        if (c[fila-1][columna] == 1 && c[fila][columna] == -1) uno ++;
    }

    if (fila+1 < tSize){
        if (c[fila+1][columna] == 0 && c[fila][columna] == -1) cero++;
        if (c[fila+1][columna] == 1 && c[fila][columna] == -1) uno ++;
    }

    if (columna-1 >= 0){
        if (c[fila][columna-1] == 0 && c[fila][columna] == -1) cero++;
        if (c[fila][columna-1] == 1 && c[fila][columna] == -1) uno ++;
    }

    if (columna+1 < tSize){
        if (c[fila][columna+1] == 0 && c[fila][columna] == -1) cero++;
        if (c[fila][columna+1] == 1 && c[fila][columna] == -1) uno ++;
    }

    if (color == 0) return cero > uno;
    else return uno > cero;
    }

int Heuristica::getValorHeuristicoRelativo(Partida p, int color)
{
    int ptsJ1 = 0;
    int ptsJ2 = 0;

    ptsJ1 = getValorHeuristico(p,1);
    ptsJ2 = getValorHeuristico(p,0);

    if (color==0) return ptsJ2 - ptsJ1;
    return ptsJ1 - ptsJ2;
}



int Heuristica::getValorHeuristico(Partida p, int color){

    int huecos = 0;
    int pts = 0;

    if (color==0){
        int p2= p.getJugador2().getPts()*constPts;
        for (int i = 0 ; i < tSize ; i++)
                for (int j = 0 ; j < tSize ; j++)
                    if (miHueco(p.getTablero().getCruces(),i,j,0))
                        huecos++;

        pts = p2 + huecos*constHuecos ;
    }
    else{

        int p1= p.getJugador1().getPts()*constPts;
        for (int i = 0 ; i < tSize ; i++)
                for (int j = 0 ; j < tSize ; j++)
                    if (miHueco(p.getTablero().getCruces(),i,j,1))
                        huecos++;
        pts = p1 + huecos*constHuecos ;
    }
    return pts;
}

Heuristica::~Heuristica(){
}
