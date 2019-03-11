#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "../include/Game.h"


Game::Game(int w, int h, std::string name)
{
    wind = new sf::RenderWindow(sf::VideoMode(w, h), name);
    jugador = new Jugador(h);
    mapa = new Mapa();

    fps = 60;
    wind->setFramerateLimit(fps);

    loop();

    delete wind;
    delete jugador;
    delete mapa;

}

void Game::loop()
{
    sf::Clock clock;
    while(wind->isOpen())
    {
        sf::Event ev;
		while (wind->pollEvent(ev)) {
			if (ev.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				wind->close();
			}
		}

        jugador->control(clock);
        jugador->jump(clock, mapa->getPuente());
        clock.restart().asMilliseconds();

        //paint
        wind->clear(sf::Color(102, 204, 255));
        jugador->dibujar(wind);
        mapa->dibujar(wind);
        wind->display();

    }
}

