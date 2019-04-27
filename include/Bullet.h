#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>

#define vel 0.3

class Bullet
{
    public:
        Bullet(sf::Texture&,int t,int p,int d,sf::Vector2f);
        virtual ~Bullet();
        void update();
        void draw(sf::RenderWindow&);
        sf::Sprite* getCollision();

    protected:

    private:
        sf::Sprite* bullet;
        int type, phase, dir;
        sf::Vector2f scale;
        sf::Clock c;
};

#endif // BULLET_H
