#include "Tablero.h"
#include <list>
#include <iostream>
using namespace std;

Tablero::Tablero(){
}

void Tablero::crear(int tSize){
    this->tSize = tSize;
    cantFichasPuestas = 0;
    crearYcargar(cruces);
}

void Tablero::crearYcargar(int** &matriz){
    matriz = new int*[tSize];
    for (int i=0;i<tSize;i++)
        matriz[i] = new int[tSize];
    for(int i=0;i<tSize;i++)
        for(int j=0;j<tSize;j++)
            matriz[i][j] = -1;
}


list<Cadena> Tablero::getCadenas() const{
    return cadenas;
}

int** Tablero::getCruces() const{
    return cruces;
}


bool Tablero::igualCruces(Tablero other){
    for (int j=0;j<tSize;j++)
        for (int i=0;i<tSize;i++)
            if (cruces[i][j] != other.getCruces()[i][j]) return false;
    return true;
}

Tablero::~Tablero(){
}

void Tablero::copiarTablero(Tablero other){
    int **aux = other.getCruces();
    for (int i=0; i<tSize; i++)
        for (int j=0; j<tSize; j++){
            int v = aux[i][j];
            cruces[i][j] = v;
            }


    if (!other.getCadenas().empty()){
        list<Cadena> aux = other.getCadenas();
        typename list<Cadena> :: iterator it = aux.begin();
        while (it != aux.end()){
            Cadena c(tSize,it->getFichas(),it->getMatriz());
            cadenas.push_back(c);
            it++;
        }
    }
}

list<Ficha> Tablero::getAdyacentes(Ficha f, int color){
    list<Ficha> adys;
    int fila = f.getFila();
    int col = f.getColumna();
    if (fila-1 >= 0 && color == cruces[fila-1][col]){
        Ficha fa(fila-1,col,cruces[fila-1][col]);
        adys.push_back(fa);
    }

    if (fila+1 < tSize && color == cruces[fila+1][col]){
        Ficha fa(fila+1,col,cruces[fila+1][col]);
        adys.push_back(fa);
    }

    if (col-1 >= 0 && color == cruces[fila][col-1]){
        Ficha fa(fila,col-1,cruces[fila][col-1]);
        adys.push_back(fa);
    }

    if (col+1 < tSize && color == cruces[fila][col+1]){
        Ficha fa(fila,col+1,cruces[fila][col+1]);
        adys.push_back(fa);
    }

    return adys;
}

bool Tablero::cantHuecos(Ficha f, int maximo) const{
    int huecos = 0;
    if (f.getFila()-1>=0 && cruces[f.getFila()-1][f.getColumna()] == -1) huecos++;
    if (f.getColumna()-1>=0 && cruces[f.getFila()][f.getColumna()-1] == -1) huecos++;
    if (f.getFila()+1<tSize && cruces[f.getFila()+1][f.getColumna()] == -1) huecos++;
    if (f.getColumna()+1<tSize && cruces[f.getFila()][f.getColumna()+1] == -1) huecos++;
    return huecos == maximo;
}

bool Tablero::cadenaCapturada(Cadena c) const{
    list<Ficha> fichas = c.getFichas();
    typename list<Ficha> :: const_iterator it = fichas.begin();
    while (it != fichas.end()){
         if (!cantHuecos(*it,0))
            return false;
        it++;
    }
    return true;
}



void Tablero::actualizarTablero(Ficha f, list<Ficha> &fichasCapturadas){

        cruces[f.getFila()][f.getColumna()] = f.getColor();
        cantFichasPuestas ++;

        bool masDeUnaCadena = false;
        bool sinCambios = true;
        list<Cadena> eliminarCadenas;
        ///compruebo si esta ficha pertenece a una o mas cadena existene, si es mas de 1, las uno y agrego la ficha f
        list<Ficha> adys = getAdyacentes(f,f.getColor());

        typename list<Cadena> :: iterator itCadena = cadenas.begin();
        typename list<Cadena> :: iterator cAux;
        //Cadena cAux(tSize);
        while (itCadena != cadenas.end()){
            typename list<Ficha> :: iterator itAdys = adys.begin();
            while (itAdys != adys.end()){
                Ficha fAd(-1,-1,-1);
                fAd.copiar(*itAdys);
                if (itCadena->pertenece(fAd) && !masDeUnaCadena && !itCadena->pertenece(f)){
                    itCadena->addFicha(f);
                    cAux = itCadena;
                    masDeUnaCadena = true;
                    sinCambios = false;
                }
                else if (itCadena->pertenece(*itAdys) && masDeUnaCadena  && !itCadena->pertenece(f)){
                    list<Ficha> laux = itCadena->getFichas();
                    typename list<Ficha> :: iterator itaux = laux.begin();
                    while (itaux != laux.end()){
                        cAux->addFicha(*itaux);
                        itaux++;
                    }
                    eliminarCadenas.push_back(*itCadena);
                }
                itAdys++;
            }
            itCadena++;
        }

        ///si no hay cadenas alrededor de la ficha f creo una cadena con los adys
        if (sinCambios){
            Cadena nc(tSize);
            nc.addFicha(f);
            typename list<Ficha> :: iterator itAdys = adys.begin();
            itAdys = adys.begin();
            while (itAdys != adys.end()){
                nc.addFicha(*itAdys);
                itAdys++;
            }
            cadenas.push_back(nc);
        }
        typename list<Cadena> :: const_iterator itElim = eliminarCadenas.begin();
        while (itElim != eliminarCadenas.end()){
            cadenas.remove(*itElim);
            itElim++;
        }
        eliminarCadenas.clear();

        if(cantFichasPuestas!=tSize*tSize){
            ///compruebo si con f se crea un cerco que elimine a otras fichas
            int color;
            if (f.getColor() == 0 ) color = 1;
            else color = 0;
            list<Ficha> adysOpuestos = getAdyacentes(f,color);
            typename list<Cadena> :: iterator itCadena2 = cadenas.begin();
            while (itCadena2 != cadenas.end()){
                typename list<Ficha> :: iterator itAdysO = adysOpuestos.begin();
                while (itAdysO != adysOpuestos.end()){
                    Ficha fAux(-1,-1,-1);
                    fAux.copiar(*itAdysO);
                    if (itCadena2->pertenece(*itAdysO)){
                        if (cadenaCapturada(*itCadena2)){
                            list<Ficha> eliminar = itCadena2->getFichas();
                            typename list<Ficha> :: const_iterator itElim = eliminar.begin();
                            while (itElim != eliminar.end()){
                                fichasCapturadas.push_back(*itElim);
                                cantFichasPuestas --;
                                cruces[itElim->getFila()][itElim->getColumna()] = -1;
                                itElim++;
                            }
                            eliminarCadenas.push_back(*itCadena2);
                        }

                    }
                    itAdysO++;
                }
                itCadena2++;
             }



            itElim = eliminarCadenas.begin();
            while (itElim != eliminarCadenas.end()){
                cadenas.remove(*itElim);
                itElim++;
            }
        }

}


