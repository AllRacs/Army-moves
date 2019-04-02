#include "Jugador.h"
#include "SFML/Graphics.hpp"
#include <iostream>

#define vel 0.2

Jugador::Jugador(int h)
{
    //ctor
    player = new sf::Texture();
    player_s = new sf::Sprite();


    player->loadFromFile("img/humvee/full-humvee.png");
    player_s->setTexture(*player);
    player_s->setOrigin({906/2, 510/2});
    player_s->setScale(-0.2, 0.2);
    player_s->setPosition(100,h/8*6);
}

Jugador::~Jugador()
{
    //dtor
    delete player_s;
    delete player;
}

void Jugador::control(sf::Clock c)
{
    sf::Time time = c.getElapsedTime();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        player_s->setScale(-0.2, 0.2);
        player_s->move({-vel * time.asMilliseconds(), 0});
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        player_s->setScale(-0.2, 0.2);
        player_s->move({vel * time.asMilliseconds(), 0});
    }
}

void Jugador::jump(sf::Clock c, sf::Sprite m)
{
    sf::Time time = c.getElapsedTime();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        player_s->move({0, -vel * time.asMilliseconds()});
    }
    else if(!player_s->getGlobalBounds().intersects(m.getGlobalBounds()))
    {
        player_s->move({0, vel * time.asMilliseconds()});
    }
}

void Jugador::dibujar(sf::RenderWindow *w)
{
    w->draw(*player_s);
    std::cout << player_s->getPosition().x << " : " << player_s->getPosition().y << std::endl;
}
