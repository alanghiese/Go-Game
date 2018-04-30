#ifndef FICHA_H
#define FICHA_H


class Ficha
{
    public:
        ///constructoras y destructor
        Ficha(int fil, int columna, int color);
        Ficha();
        ~Ficha();

        ///set and getters
        void setColor(int color) ;
        int getFila() const ;
        int getColumna() const;
        int getColor() const;
        ///devuelve true si una ficha es igual a esta
        bool equal(Ficha other) const;
        ///operador ==
        bool operator ==(const Ficha &f) const;
        ///copia los datos de la ficha other en esta
        void copiar(Ficha other);

    private:
        int fila;
        int columna;
        int color;
};

#endif // FICHA_H
