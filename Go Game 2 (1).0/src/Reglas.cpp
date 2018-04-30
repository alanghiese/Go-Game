#include "Reglas.h"

Reglas::Reglas(){
}



bool Reglas::KO(Ficha f, Tablero t, Tablero estAnt) const{
    return t.igualCruces(estAnt);
}

bool Reglas::ojo(Ficha f, Tablero t) const{
    int huecos = 0;
    if (f.getFila()-1>=0 && (t.getCruces()[f.getFila()-1][f.getColumna()] == -1 || t.getCruces()[f.getFila()-1][f.getColumna()] == f.getColor())) huecos++;
    if (f.getColumna()-1>=0 && (t.getCruces()[f.getFila()][f.getColumna()-1] == -1 || t.getCruces()[f.getFila()][f.getColumna()-1] == f.getColor())) huecos++;
    if (f.getFila()+1<tSize && (t.getCruces()[f.getFila()+1][f.getColumna()] == -1 || t.getCruces()[f.getFila()+1][f.getColumna()] == f.getColor())) huecos++;
    if (f.getColumna()+1<tSize && (t.getCruces()[f.getFila()][f.getColumna()+1] == -1 || t.getCruces()[f.getFila()][f.getColumna()+1] == f.getColor())) huecos++;
    return huecos<1;
}

bool Reglas::suicidio(Ficha f, Tablero t) const{
    list<Cadena> cadenas = t.getCadenas();
    typename list<Cadena> :: iterator itC = cadenas.begin();
    while (itC != cadenas.end()){
        if (itC->pertenece(f))
            break;
        itC++;
    }
    list<Ficha> hijos = itC->getFichas();

    typename list<Ficha> :: iterator itLista = hijos.begin();
    while (itLista != hijos.end()){
        Ficha fA(itLista->getFila(),itLista->getColumna(),itLista->getColor());
        if (!cantHuecos(fA,t,0))
            return false;
        itLista++;
    }
    return true;
}





bool Reglas::comprobar(Ficha f, Tablero t, Tablero estAnt) const{
    if  (t.getCruces()[f.getFila()][f.getColumna()] != -1)
    {
        return false;
    }
    Tablero tAux;
    list<Ficha> lista;
    list<Ficha> yaPase;
    tAux.crear(t.getSize());
    tAux.copiarTablero(t);
    tAux.actualizarTablero(f,lista);
    bool sui = suicidio(f,tAux);
    bool ko = KO(f,tAux,estAnt);
    bool oj = ojo(f,tAux);
    if (ko || oj || sui) return false;
    else return true;

}


void Reglas::getHijos(Ficha f, Tablero t, list<Ficha> &hijos, Ficha o) const
{
    Utilidad util;
    if (f.getFila()-1>=0 && t.getCruces()[f.getFila()-1][f.getColumna()] == f.getColor()){
            Ficha fAux(f.getFila()-1,f.getColumna(),f.getColor());
            if(!fAux.equal(o) && !f.equal(fAux) && !util.perteneceFichaALista(hijos,fAux)) {
                hijos.push_back(fAux);
                getHijos(fAux,t,hijos,o);
            }

    }
    if (f.getColumna()-1>=0 && t.getCruces()[f.getFila()][f.getColumna()-1] == f.getColor()) {
            Ficha fAux(f.getFila(),f.getColumna()-1,f.getColor());
             if(!fAux.equal(o) && !f.equal(fAux) && !util.perteneceFichaALista(hijos,fAux)) {
                hijos.push_back(fAux);
                getHijos(fAux,t,hijos,o);
            }
    }
    if (f.getFila()+1<tSize && t.getCruces()[f.getFila()+1][f.getColumna()] == f.getColor()) {
            Ficha fAux(f.getFila()+1,f.getColumna(),f.getColor());
             if(!fAux.equal(o) && !f.equal(fAux) && !util.perteneceFichaALista(hijos,fAux)) {
                hijos.push_back(fAux);
                getHijos(fAux,t,hijos,o);
            }
    }
    if (f.getColumna()+1<tSize && t.getCruces()[f.getFila()][f.getColumna()+1] == f.getColor()){
            Ficha fAux(f.getFila(),f.getColumna()+1,f.getColor());
             if(!fAux.equal(o) && !f.equal(fAux) && !util.perteneceFichaALista(hijos,fAux)) {
                hijos.push_back(fAux);
                getHijos(fAux,t,hijos,o);
            }
    }




}








bool Reglas::cantHuecos(Ficha f, Tablero t, int maximo) const{
    int huecos = 0;
//    int v = t.getCruces()[f.getFila()+1][f.getColumna()];
    if (f.getFila()-1>=0 && t.getCruces()[f.getFila()-1][f.getColumna()] == -1) huecos++;
    if (f.getColumna()-1>=0 && t.getCruces()[f.getFila()][f.getColumna()-1] == -1) huecos++;
    if (f.getFila()+1<tSize && t.getCruces()[f.getFila()+1][f.getColumna()] == -1) huecos++;
    if (f.getColumna()+1<tSize && t.getCruces()[f.getFila()][f.getColumna()+1] == -1) huecos++;
    return huecos == maximo;
}



Reglas::~Reglas(){
}
