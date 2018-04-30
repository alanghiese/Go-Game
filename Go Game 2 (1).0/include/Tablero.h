#ifndef TABLERO_H
#define TABLERO_H
#include <list>
#include "Cadena.h"
using namespace std;


class Tablero
{
    public:
        ///constructora y destructora
        Tablero();
        ~Tablero();

        ///crea el tablero
        void crear(int tSize);
        ///devuelve la matriz de cruces perteneciente al tablero
        int ** getCruces() const;
        ///actualiza el tablero segun una ficha
        void actualizarTablero(Ficha f, list<Ficha> &fichasCapturadas);
        ///copia el tablero con los datos de otro tablero
        void copiarTablero(Tablero other);
        ///devuelve true si un tablero tiene los cruces instanciados de igual manera
        bool igualCruces(Tablero other);
        ///retorna el tamaño del tablero
        int getSize(){return tSize;}
        ///devuelve la lista de cadenas del tablero
        list<Cadena> getCadenas() const;


    private:
        ///devuelve los adyacentes de una ficha
        list<Ficha> getAdyacentes(Ficha f, int color);
        ///crea y carga la matriz dinamica de cruces
        void crearYcargar(int **&matriz);
        ///se fija si una cadena es capturada
        bool cadenaCapturada(Cadena c) const;
        ///devuelve la cantidad de huecos alrededor de una ficha
        bool cantHuecos(Ficha f, int maximo) const;
        int ** cruces;
        list<Cadena> cadenas;
        int tSize;
        int cantFichasPuestas;
};

#endif // TABLERO_H
