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
        Player(int);
        virtual ~Player();
        void update(std::vector<sf::Sprite*> m);
        void draw(sf::RenderWindow&);
        void controlPlayer(std::vector<sf::Sprite*> m);
        void jump(std::vector<sf::Sprite*> m);
        bool bulletCollision(std::vector<sf::Sprite*>);
        int getPoints();
        int getFuel();

    protected:

    private:
        sf::Vector2f position;
        Animation *animation;
        sf::RectangleShape *collision;
        int points, fuel;

        int phase;

        sf::Clock c;
};

#endif // PLAYER_H
