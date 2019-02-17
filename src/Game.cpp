#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "../include/Game.h"

#define vel 0.2


Game::Game(int w, int h, std::string name)
{
    wind = new sf::RenderWindow(sf::VideoMode(w, h), name);
    player = new sf::Texture();
    player_s = new sf::Sprite();

    fps = 60;
    wind->setFramerateLimit(fps);

    player->loadFromFile("img/humvee/full-humvee.png");
    player_s->setTexture(*player);
    player_s->setOrigin({906/2, 510/2});
    player_s->setScale(0.2, 0.2);
    player_s->setPosition(100,h/8*6);

    loop();

    delete wind;
    delete player_s;
    delete player;
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

		control(clock);
        clock.restart().asMilliseconds();

        jump();

        //paint
        wind->clear(sf::Color(102, 204, 255));
        wind->draw(*player_s);
        wind->display();
        std::cout << player_s->getPosition().x << " : " << player_s->getPosition().y << std::endl;
    }
}

void Game::control(sf::Clock c)
{
    sf::Time time = c.getElapsedTime();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        player_s->setScale(0.2, 0.2);
        player_s->move({-vel * time.asMilliseconds(), 0});
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        player_s->setScale(-0.2, 0.2);
        player_s->move({vel * time.asMilliseconds(), 0});
    }
}

void Game::jump()
{

}
