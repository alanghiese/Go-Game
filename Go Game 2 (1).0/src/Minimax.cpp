#include "Minimax.h"
#define maxNivel 2

Minimax::Minimax()
{

}

Minimax::~Minimax(){}


void Minimax::setValores(Heuristica Heu, Reglas r)
{
    this->r = r;
    this->heuristica = Heu;
}

Ficha Minimax::nextPlay(Partida p)
{
    dupla duplafinal = minimax(p,0,0);
    Ficha fichaElegida;
    fichaElegida.copiar(duplafinal.ficha);
    return fichaElegida;
}

void Minimax::getHijos(list<dupla>& ld, Partida p, int Jugador)
{
    for (int i = 0; i < p.getTablero().getSize(); i++)
        for (int j = 0; j < p.getTablero().getSize(); j++){
            Ficha f(i,j,Jugador);
            if (p.jugadaPosible(f)){
                dupla d;
                Partida pAux;
                pAux.setTsize(p.getTablero().getSize());
                pAux.copiar(p);
                list<Ficha> lc;
                pAux.actualizarTablero(f,lc);
                int valorheu = heuristica.getValorHeuristicoRelativo(pAux,0);
                d.valor = valorheu;
                d.ficha = f;
                ld.push_back(d);
            }
        }


}


Minimax::dupla Minimax::minimax(Partida p, int nivel, int jug)
{
    bool hoja = esHoja(p.getTablero());
    if ( hoja || nivel == maxNivel){
        list<dupla> listaDuplas;
        dupla duplaS;
        if (!hoja){
            getHijos(listaDuplas,p,jug);
            if (!listaDuplas.empty())
                if (jug==0) duplaS = maximo(listaDuplas);
                else duplaS = minimo(listaDuplas);
            else{
                Ficha fa(-1,-1,-1);
                duplaS.ficha = fa;
                duplaS.valor = heuristica.getValorHeuristicoRelativo(p,0);
            }
        }
        else{
            Ficha f(-1,-1,-1);
            duplaS.ficha = f;
            duplaS.valor = heuristica.getValorHeuristicoRelativo(p,0);
        }


        return duplaS;
    }
    else{
        if (jug == 0){
            list<dupla> minimos;
            nivel++;
            int poda = -32000;
            bool jugo = false;
            for (int i = 0; i < p.getTablero().getSize(); i++)
                for (int j = 0; j < p.getTablero().getSize(); j++){
                    Ficha f(i,j,jug);
                    if (p.jugadaPosible(f)){
                        jugo = true;
                        list<Ficha> lc;
                        Partida pAux;
                        pAux.setTsize(p.getTablero().getSize());
                        pAux.copiar(p);
                        pAux.actualizarTablero(f,lc);
                        int valHeu = heuristica.getValorHeuristicoRelativo(pAux,0);
                        if(poda<valHeu){
                            jug = 1;
                            poda = valHeu;
                            dupla d = minimax(pAux,nivel,jug);
                            jug = 0;
                            d.ficha = f;
                            minimos.push_back(d);
                        }
                    }

                }
            if (jugo){
                dupla finalD = maximo(minimos);
                return finalD;
            }
            else{
                dupla finalD;
                Ficha fa(-1,-1,-1);
                finalD.ficha = fa;
                finalD.valor = heuristica.getValorHeuristicoRelativo(p,0);
                return finalD;
            }
            }
        else{
            list<dupla>  maximos;
            nivel++;
            int poda = 32000;
            for (int i = 0; i < p.getTablero().getSize(); i++)
                for (int j = 0; j < p.getTablero().getSize(); j++){
                Ficha f(i,j,jug);
                if (p.jugadaPosible(f)){
                    list<Ficha> lc;
                    Partida pAux;
                    pAux.setTsize(p.getTablero().getSize());
                    pAux.copiar(p);
                    pAux.actualizarTablero(f,lc);
                    int valHeu = heuristica.getValorHeuristicoRelativo(pAux,0);
                    if(poda>valHeu){
                        jug = 0;
                        dupla d = minimax(pAux,nivel,jug);
                        jug = 1;
                        poda = valHeu;
                        d.ficha = f;
                        maximos.push_back(d);
                    }
                }
            }
            return minimo(maximos);
            }
    }
}

Minimax::dupla Minimax::minimo(list<dupla>l)
{
    Ficha f(-1,-1,-1);
    dupla mini;
    mini.valor = 999;
    mini.ficha = f;
    dupla d;
    typename list<dupla> :: iterator it = l.begin();
    while (it!=l.end()){
        d = *it;
        if(mini.valor>=d.valor)
            mini = d;
        it++;
    }
    return mini;
}

Minimax::dupla Minimax::maximo(list<dupla>l)
{
    Ficha f(-1,-1,-1);
    dupla maxi;
    maxi.valor = -999;
    maxi.ficha = f;
    dupla d;
    typename list<dupla> :: iterator it = l.begin();
    while (it!=l.end()){
        d = *it;
        if(maxi.valor<=d.valor)
            maxi = d;
        it++;
    }
    return maxi;
}


bool Minimax::esHoja(Tablero t) const
{
    for(int i=0;i<t.getSize();i++)
        for(int j=0;j<t.getSize();j++)
            if (t.getCruces()[i][j] == -1) return false;
    return true;
}
