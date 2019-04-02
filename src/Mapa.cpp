#include "Mapa.h"
#include <iostream>


Mapa::Mapa()
{
    //ctor
    for(int a = 0; a < PUENTES; a++)
    {
        puentes_t[a].loadFromFile("img/rect.JPG");
        puentes_s[a].setTexture(puentes_t[a]);
    }
}

Mapa::~Mapa()
{
    //dtor
}

sf::Sprite Mapa::getPuente()
{
    return puentes_s[0];
}

void Mapa::dibujar(sf::RenderWindow *w)
{
    puentes_s[0].setPosition(20.f, 600.f);
    w->draw(puentes_s[0]);
}
