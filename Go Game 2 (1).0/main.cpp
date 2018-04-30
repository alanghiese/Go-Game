#include <SFML/Graphics.hpp>
#include <stddef.h>
#include <string>
#include <sstream>
#include <time.h>
#include <iostream>
#include "include/Reglas.h"
#include "include/Partida.h"
#include "include/Ficha.h"
#include "Heuristica.h"
#include "Minimax.h"

using namespace sf;

int tSize, tamX, tamY;
int size = 37;
int sizebetween = 50;
int jugador = 1;
int n = 0;
int constPts = 1,constHuecos = 1;
Reglas r;
Texture menu, menut, menuia, fichas, creditos, t5x5, t9x9;
Partida p;
Sprite f[360];
Minimax minimax;

bool validarPos(Vector2i posActual, int &x, int &y, int &coordx, int &coordy)
{
    bool correcto = false;
    for (int i = 0; i < tSize; i++)
    {
        if ( 65*i+15 < posActual.x && posActual.x < (65*i+55))
        {
            int aux = 40+ 65*i ;
            coordx = aux - size/2;
            y = i;
            correcto = true;
            break;
        }

    }
    if (!correcto) return false;
    for (int j = 0; j < tSize; j++)
    {
        correcto = false;
        if ( 65*j+15 < posActual.y && posActual.y < (65*j+55))
        {
            int aux =40+ 65*j ;
            coordy = aux - size/2;
            x = j;
            correcto = true;
            break;
        }

    }

    return correcto;
}
int actualizarSprites(list<Ficha> &fichasCapturadas)
{
    typename list<Ficha> :: const_iterator itLista = fichasCapturadas.begin();
    while (itLista != fichasCapturadas.end())
    {
        int coordx = (40+ 65*(itLista->getColumna())) - size/2;
        int coordy = (40+ 65*(itLista->getFila())) - size/2;
        for(int i=0;i<n;i++)
        {
            Vector2f aux= f[i].getPosition();
            if (aux.x == coordx && aux.y == coordy )
            {
                Texture empty;
                f[i].setTexture(empty);
                f[i].setPosition(-50,-50);
            }
        }
        itLista++;
    }
    fichasCapturadas.clear();
    return 0;

}
void mostrarResultado(int puntosj1, int puntosj2)
{
    RenderWindow reswindow(VideoMode(200,200), "Resultado");
    Texture fondo;
    fondo.loadFromFile("source/fondo.png");
    Sprite sFondo(fondo);
    Font font;
    font.loadFromFile("source/impact.ttf");
    Text text;
    text.setFont(font);
    text.setColor(Color::White);
    text.setCharacterSize(15);
    Text text2;
    text2.setFont(font);
    text2.setColor(Color::White);
    text2.setCharacterSize(15);
    std::string mensaje;
    std::string mensaje2;
    std::string pj1 = static_cast<ostringstream*>( &(ostringstream() << puntosj1) )->str();
    std::string pj2 = static_cast<ostringstream*>( &(ostringstream() << puntosj2) )->str();

    if (puntosj1 > puntosj2){
        mensaje = "El ganador es el Jugador 1";
        mensaje2 = "J1 = ";
        mensaje2 = mensaje2 + pj1;
        mensaje2 = mensaje2 + "   ";
        mensaje2 = mensaje2 + "J2 = ";
        mensaje2 = mensaje2 + pj2;

    }
    else{
        mensaje = "El ganador es el Jugador 2";
        mensaje2 = "J1 = ";
        mensaje2 = mensaje2 + pj1;
        mensaje2 = mensaje2 + "   ";
        mensaje2 = mensaje2 + "J2 = ";
        mensaje2 = mensaje2 + pj2;
    }
    text.setString(mensaje);
    text2.setString(mensaje2);
    while(reswindow.isOpen())
    {
        Event event;
        while(reswindow.pollEvent(event))
    {
        if(event.type == Event::Closed)
        {
            reswindow.close();
        }
    }
    text.setPosition(15,50);
    text2.setPosition(55,100);
    reswindow.clear(Color::White);
    reswindow.draw(sFondo);
    reswindow.draw(text);
    reswindow.draw(text2);
    reswindow.display();
    }
}

int iniciarPartida(int jugadores, int heuristica, int tablero)
{
    Sprite sBoard;
    if (tablero == 1){
       sBoard.setTexture(t5x5);
       tSize = 5;
       p.setTsize(tSize);
       tamX = 340;
       tamY = 340;
    }
    else{
        sBoard.setTexture(t9x9);
        tSize = 9;
        p.setTsize(tSize);
        tamX = 600;
        tamY = 601;
    }
    RenderWindow window(VideoMode(tamX,tamY), "Go Game!");
    if ( jugadores == 2)
        p.setJugadores(1,0); ///REVISAR
    else{
        p.setJugadores(1,0);
        ///configurar ia con la heuristica
        if (heuristica==1){
            Heuristica h(20,5,tSize);
            minimax.setValores(h,r);
        }
        else if(heuristica==2){
            Heuristica h(5,3,tSize);
            minimax.setValores(h,r);
        }
        else{
            Heuristica h(1,20,tSize);
            minimax.setValores(h,r);
        }
    }
    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window);

        Event e;
        list<Ficha> fichasCapturadas; ///ACA RETORNAMOS LA LISTA DE FICHAS A SER BORRADAS DEL TABLERO
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
            if(e.type == Event::MouseButtonPressed)
                if(Mouse::isButtonPressed(Mouse::Left))
                        {
                            if ((257< pos.x  && pos.x < 334) && (314 < pos.y && pos.y <336) &&(tablero == 1)) ///5x5 Terminar
                            {
                                int j1,j2;
                                p.getPuntuaciones(j1,j2,1,1);
                                mostrarResultado(j1,j2);
                                window.close();
                            }
                            if ((502< pos.x  && pos.x < 591) && (571 < pos.y && pos.y <594) &&(tablero != 1)) ///9x9 Terminar
                            {
                                int j1,j2;
                                p.getPuntuaciones(j1,j2,constPts,constHuecos);
                                mostrarResultado(j1,j2);
                                window.close();
                            }
                            int coordx = 0, coordy = 0, x = 0, y = 0;
                            if (validarPos(pos, x, y, coordx, coordy)) ///x = logico coordx = grafico
                            {
                                Ficha ficha(x,y,jugador);
                                if (p.jugadaPosible(ficha))
                                    {
                                        p.actualizarTablero(ficha,fichasCapturadas);

                                        f[n].setTexture(fichas);
                                        f[n].setTextureRect( IntRect(size*jugador,0,size,size) );
                                        f[n].setPosition(coordx,coordy);
                                        n++; ///N NO PUEDE SUPERAR 360

                                        if (jugadores!=2){
                                            if (n >= 2) actualizarSprites(fichasCapturadas); ///si ya se jugaron 2 fichas pruebo
                                            window.clear();
                                            window.draw(sBoard);
                                            for(int i=0;i<n;i++) window.draw(f[i]);
                                            window.display();
                                        }


                                        if (jugador == 0) jugador = 1;
                                        else jugador = 0;
                                        ///para el caso de player vs IA
                                        if (jugadores!=2){
                                            Ficha fIA = minimax.nextPlay(p);
                                            Ficha fin(-1,-1,-1);
                                            if (!fin.equal(fIA)){
                                                int coordx2 = 40+ 65*fIA.getColumna() - size/2;
                                                int coordy2 = 40+ 65*fIA.getFila() - size/2;
                                                f[n].setTexture(fichas);
                                                f[n].setTextureRect( IntRect(size*jugador,0,size,size) );
                                                f[n].setPosition(coordx2,coordy2);
                                                n++; ///N NO PUEDE SUPERAR 360

                                                p.actualizarTablero(fIA,fichasCapturadas);
                                            }
                                            else{
                                                int j1,j2;
                                                p.getPuntuaciones(j1,j2,constPts,constHuecos);
                                                mostrarResultado(j1,j2);
                                                window.close();
                                            }

                                            jugador = 1;

                                        }
                                   }
                            }
                        }
        if (n >= 2) actualizarSprites(fichasCapturadas); ///si ya se jugaron 2 fichas pruebo
        window.clear();
        window.draw(sBoard);
        for(int i=0;i<n;i++) window.draw(f[i]);
        window.display();
        }

    }
    return 0;
}

int seleccionarTablero(int heuristica)
{
    RenderWindow tabWindow(VideoMode(396,516), "Menu Tablero");
    Sprite tabMenu(menut);

    int jugadores;
    if (heuristica == 0)
        jugadores = 2;
    else jugadores = 1;

    while (tabWindow.isOpen())
    {
        Vector2i pos = Mouse::getPosition(tabWindow);
        Event e;
        while (tabWindow.pollEvent(e))
        {
            if (e.type == Event::Closed)
                tabWindow.close();
            if(e.type == Event::MouseButtonPressed)
                if(Mouse::isButtonPressed(Mouse::Left))
                        {
                            if ((27< pos.x  && pos.x < 182) && (162 < pos.y && pos.y <319)) ///5x5
                              {
                                tabWindow.close();
                                iniciarPartida(jugadores, heuristica, 1);
                              }
                            else if ((215< pos.x  && pos.x < 370) && (164 < pos.y && pos.y <316))///9x9
                            {
                                tabWindow.close();
                                iniciarPartida(jugadores, heuristica, 2);
                            }
                            else if ((148< pos.x  && pos.x < 264) && (433 < pos.y && pos.y <481)) ///SALIR
                            {
                                tabWindow.close();
                            }
                        }
        tabWindow.clear();
        tabWindow.draw(tabMenu);
        tabWindow.display();
        }

    }
    return 0;

}

int configuraria()
{
    RenderWindow iaWindow(VideoMode(398,422), "Menu IA");
    Sprite iaMenu(menuia);
    int heuristica;
    while (iaWindow.isOpen())
    {
        Vector2i pos = Mouse::getPosition(iaWindow);
        Event e;
        while (iaWindow.pollEvent(e))
        {
            if (e.type == Event::Closed)
                iaWindow.close();
            if(e.type == Event::MouseButtonPressed)
                if(Mouse::isButtonPressed(Mouse::Left))
                        {
                            if ((37< pos.x  && pos.x < 118) && (219 < pos.y && pos.y <267)) ///IA1
                              {
                                iaWindow.close();
                                heuristica = 1;
                                seleccionarTablero(heuristica);
                              }
                            else if ((158< pos.x  && pos.x < 244) && (219 < pos.y && pos.y <267))///IA2
                            {
                                iaWindow.close();
                                heuristica = 2;
                                seleccionarTablero(heuristica);
                            }
                            else if ((285< pos.x  && pos.x < 372) && (219 < pos.y && pos.y <267)) ///IA3
                            {
                                iaWindow.close();
                                seleccionarTablero(heuristica);
                                heuristica = 3;
                            }
                            else if ((141< pos.x  && pos.x < 258) && (345 < pos.y && pos.y <398)) ///SALIR
                            {
                                iaWindow.close();
                            }
                        }
        iaWindow.clear();
        iaWindow.draw(iaMenu);
        iaWindow.display();
        }

    }
    return 0;

}
int mostrarCreditos()
{
    RenderWindow credWindow(VideoMode(223,237), "Creditos");
    Sprite credMenu(creditos);

    while (credWindow.isOpen())
    {
        Vector2i pos = Mouse::getPosition(credWindow);
        Event e;
        while (credWindow.pollEvent(e))
        {
            if (e.type == Event::Closed)
                credWindow.close();
            if(e.type == Event::MouseButtonPressed)
                if(Mouse::isButtonPressed(Mouse::Left))
                        {
                            if ((93< pos.x  && pos.x < 132) && (200 < pos.y && pos.y <214)) ///SALIR
                            {
                                credWindow.close();
                            }
                        }
        credWindow.clear();
        credWindow.draw(credMenu);
        credWindow.display();
        }

    }
    return 0;

}


int main()
{
    RenderWindow fwindow(VideoMode(397,596), "Go Game!");
    fichas.loadFromFile("source/fichas.png");
    t5x5.loadFromFile("source/board5x5.png");
    t9x9.loadFromFile("source/board9x9.png");///MODIFICADO
    menu.loadFromFile("source/menu.png");
    menuia.loadFromFile("source/menuia.png");
    menut.loadFromFile("source/menutableros.png");
    creditos.loadFromFile("source/creditos.png");

    Sprite sMenu(menu);
    while (fwindow.isOpen())
    {
        Vector2i pos = Mouse::getPosition(fwindow);
        Event e;
        while (fwindow.pollEvent(e))
        {
            if (e.type == Event::Closed)
                fwindow.close();
            if(e.type == Event::MouseButtonPressed)
                if(Mouse::isButtonPressed(Mouse::Left))
                        {
                            if ((84 < pos.x  && pos.x < 309) && (212 < pos.y && pos.y <263)) ///1 JUGADOR
                            {
                                fwindow.close();
                                configuraria();
                            }
                            else if ((58< pos.x && pos.x < 346) && (351< pos.y && pos.y < 401)) ///2 JUGADORES
                            {
                                fwindow.close();
                                seleccionarTablero(0);
                            }
                            else if ((353 < pos.x && pos.x < 384) && (557< pos.y && pos.y < 585)) ///COPYRIGHT(?)
                            {
                                mostrarCreditos();
                            }
                            else if ((133 < pos.x && pos.x < 253) && (505< pos.y && pos.y < 563)) ///SALIR
                            {
                                fwindow.close();
                            }
                        }
        fwindow.clear();
        fwindow.draw(sMenu);
        fwindow.display();
        }
    }
    return 0;
}

