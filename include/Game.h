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
        sf::Clock clock, cShootQ, cShootW, cDamageCD;
        sf::Texture *spritesheet;
        bool godMode;

        //phase 1 & 2 and player
        Map **mapp, *map1, *map2;
        Player *player;
        int state;

        //HUD
        HUD *hud;

        //game init and states
        void initGame(int);
        void initMap1();
        void initMap2();
        void initPlayer();
        void manageEvents();
        void switchState(int);
        void endPhase1();
        void endPhase2();

        //player & enemy logic
        bool bulletCollision();
        bool enemyCollision();
        void checkLives();
        void GODMODE();
};

#endif // GAME_H
