#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>

#include "HUD.h"
#include "Player.h"
#include "Map1.h"
#include "Map2.h"

class Game
{
    public:
        Game();
        virtual ~Game();
        void gameLoop();
        void update();
        void draw();

    protected:

    private:
        //management
        sf::RenderWindow *window;
        sf::View *view;
        sf::Event *event;
        sf::Clock clock;
        sf::Texture *spritesheet;

        //phase 1 & 2 and player
        Map **mapp, *map1, *map2;
        Player *player;
        int state;

        //HUD
        HUD *hud;

        void initGame(int);
        void initMap1();
        void initMap2();
        void initPlayer();
        void manageEvents();
        void switchState(int);
};

#endif // GAME_H
