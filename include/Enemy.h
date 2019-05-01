#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>

#include "Animation.h"

#define velCar -0.4
#define vel -0.25

#define velAC 0.2 //antiaircraft vel

class Enemy
{
    public:
        Enemy(sf::Texture&,int,int,sf::Vector2f,bool);
        virtual ~Enemy();
        void update(std::vector<sf::Sprite*>);
        void draw(sf::RenderWindow&);
        void controlEnemy(std::vector<sf::Sprite*> m);
        void jump(std::vector<sf::Sprite*> m);
        bool shoot();

        sf::RectangleShape* getCollision();

        int getType();
        void showCollisions();

    protected:

    private:
        sf::Vector2f position;
        Animation *a_movement;
        sf::RectangleShape *collision;

        int phase, type, dir, jetBehavior, jetState;
        bool jumping, jumpUp, jumpDown, seeCollisions, shootSignal;
        float baseJump, grav;

        int ammo;
        // for move, for cars, for jets
        sf::Clock c, cjump, wait2shoot;

};

#endif // ENEMY_H
