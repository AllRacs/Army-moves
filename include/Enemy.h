#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>

#include "Animation.h"

#define velCar -0.4
#define vel -0.25

class Enemy
{
    public:
        Enemy(int,int,sf::Vector2f);
        virtual ~Enemy();
        void update(std::vector<sf::Sprite*>);
        void draw(sf::RenderWindow&);
        void controlEnemy(std::vector<sf::Sprite*> m);
        void jump(std::vector<sf::Sprite*> m);
        bool shoot();

        sf::RectangleShape* getCollision();

    protected:

    private:
        Animation *animation;

        sf::Vector2f position;
        Animation *a_movement;
        sf::RectangleShape *collision;

        int phase, type;
        bool flagJump;
        float baseJump, grav;

        int ammo;

        sf::Clock c, cjump;

};

#endif // ENEMY_H
