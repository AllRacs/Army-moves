#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>

#include "Animation.h"

#define vel 0.2

class Player
{
    public:
        Player();
        virtual ~Player();
        void update(std::vector<sf::Sprite*> m);
        void draw(sf::RenderWindow&);
        void controlPlayer(std::vector<sf::Sprite*> m);
        void jump(std::vector<sf::Sprite*> m);
        int getPoints();
        int getFuel();

    protected:

    private:
        sf::Vector2f position;
        Animation *animation;
        sf::RectangleShape *colision;
        int points, fuel;

        sf::Clock c;
};

#endif // PLAYER_H
