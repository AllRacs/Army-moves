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
        void update(int,int);
        void draw(sf::RenderWindow&);

    protected:

    private:
        sf::Sprite layout;
        sf::Sprite *iconplayer;

        sf::Font *pixelFont;
        sf::Text *points;
        sf::Text *fuel;
        int ipoints, ifuel;

        sf::Clock cfuel, cpoints, cpos;

        void updateFuel(int);
        void updatePoints(int);
        void updatePos();
};

#endif // HUD_H
