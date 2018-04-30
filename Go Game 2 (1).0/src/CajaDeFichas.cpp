#include "CajaDeFichas.h"
#include <list>
#include <iostream>
using namespace std;

CajaDeFichas::CajaDeFichas(){
}

CajaDeFichas::CajaDeFichas(int color){
    assign(color);
}

void CajaDeFichas::assign(int color){
    disponibles = 180;
    this->color = color;
}

int CajaDeFichas::getDisponibles() const {
    return disponibles;
}

int CajaDeFichas::getColor() const {
    return color;
}

void CajaDeFichas::usarFicha() {
    disponibles--;
}
void CajaDeFichas::copiar(CajaDeFichas other)
{
    this->setColor(other.getColor());
    this->disponibles = other.getDisponibles();
}


void CajaDeFichas::setColor(int color)
{
   this->color = color;
}





CajaDeFichas::~CajaDeFichas(){
}
