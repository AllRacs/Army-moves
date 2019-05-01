#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#include "Animation.h"

#define vel 0.2

class Player
{
    public:
        Player(sf::Texture&,int);
        virtual ~Player();
        void update(std::vector<sf::Sprite*>);
        void draw(sf::RenderWindow&);
        void controlPlayer(std::vector<sf::Sprite*> m);
        void jump(std::vector<sf::Sprite*> m);

        int getPoints();
        int getFuel();
        int getLives();

        void updatePoints(int);
        void reposition();
        void recieveDamage();

        sf::RectangleShape* getCollision();

        void showCollisions();
        void changeGodMode(bool);

    protected:

    private:
        sf::Vector2f position;
        Animation *a_movement, *a_forward;
        sf::RectangleShape *collision;

        int points, fuel, lives, dir;
        sf::Clock cpoints, cfuel, clives;
        void updatePoints();
        void updateFuel();

        int phase;
        bool flagJump, fin, seeCollisions, godMode;
        float baseJump, grav;

        sf::Event event;
        sf::Clock c, cjump;
};

#endif // PLAYER_H
