#include "Jugador.h"



Jugador::Jugador(){
    pts = 0;
}

void Jugador::setColor(int color){
    caja.assign(color);
    pts = 0;
}

int Jugador::getCantDisp() const {
    return caja.getDisponibles();
}



int Jugador::getColor() const {
    return caja.getColor();
}

CajaDeFichas Jugador::getCajaDeFichas(){
    return caja;
}
void Jugador::setCajaDeFichas(CajaDeFichas caja){
    this->caja.copiar(caja);
}


int Jugador::getPts()
{
    return pts;
}

void Jugador::addPts(int x)
{
    pts = pts + x;
}


void Jugador::copiar(Jugador other){
    this->setCajaDeFichas(other.getCajaDeFichas());
    this->setColor(other.getColor());
    this->pts = other.getPts();
}

Jugador::~Jugador(){
}
