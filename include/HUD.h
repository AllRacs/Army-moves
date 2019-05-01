#ifndef HUD_H
#define HUD_H
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include <string>

class HUD
{
    public:
        HUD(sf::Texture&,int);
        virtual ~HUD();
        void update(int,int,int);
        void draw(sf::RenderWindow&);
        int getPoints();
        int getFuel();
        void showInfo();
        void changeGodMode(bool);

    protected:

    private:
        sf::Sprite layout;
        sf::Sprite *iconplayer;

        sf::Vector2f scale;
        sf::Clock cEndPoint;

        sf::Font *pixelFont;
        sf::Text *info;
        sf::Text *controls;
        sf::Text *points;
        sf::Text *fuel;
        sf::Text *lives;
        sf::Text *phase1start, *phase2start;
        sf::Text *phase2end, *phase2end2, *endPoint;
        int ipoints, ifuel, ilives, phase, pointCount;
        bool toogleInfo, godMode;

        void updateFuel(int);
        void updatePoints(int);
        void updateLives(int);
        void updateEndPoint();
};

#endif // HUD_H
