#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>

class Animation
{
    public:
        Animation(sf::Texture,float,float,float,float, int);
        virtual ~Animation();
        void update();
        void draw(sf::RenderWindow&);
        void die();

    protected:

    private:
        sf::Sprite *sprite;
        sf::Clock clock;
        int pos, x, y, w, h, nmax;
};

#endif // ANIMATION_H
