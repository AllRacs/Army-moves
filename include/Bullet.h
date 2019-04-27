#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>

#define vel 0.35

class Bullet
{
    public:
        Bullet(sf::Texture&,int,int,int,sf::Vector2f);
        virtual ~Bullet();
        void update();
        void draw(sf::RenderWindow&);
        sf::Sprite* getCollision();

    protected:

    private:
        sf::Sprite* bullet;
        int type, phase, dir;

        sf::Clock c;
};

#endif // BULLET_H
