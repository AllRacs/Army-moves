#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "Enemy.h"
#include "Bullet.h"

class Map
{
    public:
        Map();
        virtual ~Map();
        virtual void update();
        virtual void draw(sf::RenderWindow&);
        virtual void controlIA();

    protected:
        std::vector<Enemy> enemies;
        std::vector<Bullet> bullets;

    private:
        int ifuel, ipoints;

};

#endif // MAP_H
