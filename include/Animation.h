#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>

class Animation
{
    public:
        Animation(sf::Texture&,float,float,float,float,int,sf::Vector2f,float,int);
        virtual ~Animation();
        void update();
        void draw(sf::RenderWindow&);
        void movement(sf::Vector2f);
        void reposition(sf::Vector2f);

    protected:

    private:
        sf::Sprite *sprite;
        sf::Clock clock;
        int pos, x, y, w, h, nmax, dir;
        float vel;
        sf::Vector2f scale;
};

#endif // ANIMATION_H
