#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Game.h"

int main()
{
    /*
    sf::RenderWindow window(sf::VideoMode(1240, 720), "SFML works!");
    window.setPosition({100,100});
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            window.close();
        }
        if(shape.getPosition().y < 500){
            shape.move(0, 0.2f);
        }
        std::cout << shape.getPosition().x << " : " << shape.getPosition().y << std::endl;
        window.clear();
        window.draw(shape);
        window.display();
    }
    */

    Game *game = new Game(1240, 720, "Army moves");
    delete game;

    return 0;
}
