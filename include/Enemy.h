#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>

#include "Animation.h"

class Enemy
{
    public:
        Enemy(int);
        virtual ~Enemy();
        void draw(sf::RenderWindow&);

    protected:

    private:
        Animation *animation;
};

#endif // ENEMY_H
