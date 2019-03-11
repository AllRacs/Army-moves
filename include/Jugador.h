#ifndef JUGADOR_H
#define JUGADOR_H
#include "SFML/Graphics.hpp"


class Jugador
{
    public:
        Jugador(int h);
        virtual ~Jugador();
        void control(sf::Clock c);
        void jump(sf::Clock c, sf::Sprite m);
        void dibujar(sf::RenderWindow *w);

    protected:

    private:
        sf::Texture *player;
        sf::Sprite *player_s;

};

#endif // JUGADOR_H
