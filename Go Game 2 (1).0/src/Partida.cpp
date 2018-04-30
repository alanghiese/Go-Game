#include "Partida.h"
#include "Heuristica.h"

Partida::Partida(){
}

void Partida::setTsize(int tSize)
{
    this->tSize = tSize;
    t.crear(tSize);
    tAnt.crear(tSize);
    tAntAnt.crear(tSize);
    r.setTSize(tSize);
}

void Partida::setJugadores(int colorJug1, int colorJug2){
    j1.setColor(colorJug1);
    j2.setColor(colorJug2);
}


bool Partida::jugadaPosible(Ficha f){
        if (f.getColor() == 0){
            if (j1.getCantDisp()>0)
                return r.comprobar(f,t,tAntAnt);
        }
        else {
            if (j2.getCantDisp()>0)
                return r.comprobar(f,t,tAntAnt);
        }
    return false;
}

void Partida::actualizarTablero(Ficha f, list<Ficha> &fichasCapturadas){
    tAnt.copiarTablero(t);
    tAntAnt.copiarTablero(tAnt);
    t.actualizarTablero(f,fichasCapturadas);
    if (f.getColor() == 1){
        j1.getCajaDeFichas().usarFicha();
        j1.addPts(fichasCapturadas.size());
    }
    else{
        j2.getCajaDeFichas().usarFicha();
        j2.addPts(fichasCapturadas.size());
    }
}

void Partida::copiar(Partida other)
{
    this->setJugador1(other.j1);
    this->setJugador2(other.j2);
    this->setTablero(other.getTablero());
    this->setTableroAnt(other.getTableroAnt());
    this->setTableroAntAnt(other.getTableroAntAnt());
}

Jugador Partida::getJugador1()
{
    return this->j1;
}

Jugador Partida::getJugador2()
{
    return this->j2;
}

Tablero Partida::getTableroAnt()
{
    return this->tAnt;
}

Tablero Partida::getTableroAntAnt()
{
    return this->tAntAnt;
}

void Partida::setJugador1(Jugador j1)
{
    return this->j1.copiar(j1);
}

void Partida::setJugador2(Jugador j2)
{
    return this->j2.copiar(j2);
}

void Partida::setTablero(Tablero t)
{
    return this->t.copiarTablero(t);
}

void Partida::setTableroAnt(Tablero ant)
{
    return this->tAnt.copiarTablero(ant);
}

void Partida::setTableroAntAnt(Tablero antant)
{
    return this->tAntAnt.copiarTablero(antant);
}
void Partida::getPuntuaciones(int &pj1, int &pj2, int constPts, int constHuecos)
{
    Heuristica heuristica(constPts,constHuecos,tSize);

    pj1 = heuristica.getValorHeuristico(*this,1);
    pj2 = heuristica.getValorHeuristico(*this,0);
}

Partida::~Partida(){
}
