#ifndef MAPA_H
#define MAPA_H
#include "SFML/Graphics.hpp"
#define PUENTES 3


class Mapa
{
    public:
        Mapa();
        virtual ~Mapa();
        void dibujar(sf::RenderWindow *w);
        sf::Sprite getPuente();

    protected:

    private:
        sf::Texture puentes_t [PUENTES];
        sf::Sprite puentes_s [PUENTES];
};

#endif // MAPA_H
