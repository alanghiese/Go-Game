#include "Ficha.h"

Ficha::Ficha(){

}

Ficha::Ficha(int fila, int columna, int color){
    this->fila = fila;
    this->columna = columna;
    this->color = color;
}

void Ficha::setColor(int color){
    this->color = color;
}

int Ficha::getFila() const {
    return this->fila;
}

int Ficha::getColumna() const {
    return this->columna;
}

int Ficha::getColor() const {
    return color;//this->color;
}

void Ficha::copiar(Ficha other)
{
    this->fila = other.getFila();
    this->columna = other.getColumna();
    this->color = other.getColor();
}


bool Ficha::operator==(const Ficha& f) const
{
    return this->equal(f);
}

bool Ficha::equal(Ficha other)const{
    return this->fila == other.getFila() && this->columna == other.getColumna() && this->color == other.getColor();
}

Ficha::~Ficha(){
}
