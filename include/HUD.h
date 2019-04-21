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

    protected:

    private:
        sf::Sprite layout;
        sf::Sprite *iconplayer;

        sf::Vector2f scale;

        sf::Font *pixelFont;
        sf::Text *points;
        sf::Text *fuel;
        sf::Text *lives;
        int ipoints, ifuel, ilives;

        void updateFuel(int);
        void updatePoints(int);
        void updateLives(int);
};

#endif // HUD_H
