#include "Game.h"

Game::Game()
{
    //ctor
    window = new sf::RenderWindow(sf::VideoMode(900*1.2, 600*1.2), "Army-moves MSX");
    window->setFramerateLimit(60);
    view = new sf::View;
    window->setView(*view);

    event = new sf::Event;

    spritesheet = new sf::Texture;
    spritesheet->loadFromFile("img/army_moves_spritesheet.png");

    state = 1;
    initGame(state);


    hud = new HUD(*spritesheet, state);


    gameLoop();

}

Game::~Game()
{
    //dtor
    delete event;
    delete hud;
    delete view;
    delete window;
    if(state==1)
    {
        delete map1;
    }
    else if(state==2)
    {
        delete map2;
    }
}

void Game::initGame(int s)
{
    switch(s)
    {
        case 1:
            initMap1();
            break;
        case 2:
            initMap2();
            break;
    }
    initPlayer();
}

void Game::initMap1()
{
    map1 = new Map1(*spritesheet);
    mapp = &map1;
}

void Game::initMap2()
{
    map2 = new Map2(*spritesheet);
    mapp = &map2;
}

void Game::initPlayer()
{
    player = new Player(state);
}

void Game::manageEvents()
{
    while(window->pollEvent(*event))
    {
        switch(event->type)
        {
            case sf::Event::KeyPressed:
                if(event->key.code == sf::Keyboard::F1)
                {
                    switchState(1);
                }
                else if(event->key.code == sf::Keyboard::F2)
                {
                    switchState(2);
                }
                else if(event->key.code == sf::Keyboard::Escape)
                {
                    window->close();
                }
                break;

        }
    }
}

void Game::switchState(int s)
{
    if(s == 1)
    {
        delete player;
        if(state==1)
        {
            delete map1;
            state = s;
        }
        else if(state==2)
        {
            delete map2;
            state = s;
        }
        //delete mapp;
        std::cout << std::endl << "Map 1 Restart" << std::endl;
        initGame(1);
    }
    else if(s == 2)
    {
        delete player;
        if(state==1)
        {
            delete map1;
            state = s;
        }
        else if(state==2)
        {
            delete map2;
            state = s;
        }
        //delete mapp;
        std::cout << std::endl << "Map 2 Restart" << std::endl;
        initGame(2);
    }
}

void Game::gameLoop()
{
    while(window->isOpen())
    {
        manageEvents();

        update();

        draw();

    }
}

void Game::update()
{
    if(state == 1)
    {
        player->update(dynamic_cast<Map1*>(*mapp)->getBridges());
        dynamic_cast<Map1*>(*mapp)->update();
    }
    else if(state == 2)
    {
        player->update(dynamic_cast<Map2*>(*mapp)->getFloor());
        dynamic_cast<Map2*>(*mapp)->update();
    }

    hud->update(player->getFuel(), player->getPoints());


}

void Game::draw()
{
    window->clear(sf::Color::Black);

    if(state==1)
    {
        dynamic_cast<Map1*>(*mapp)->draw(*window);
    }
    else if(state==2)
    {
        dynamic_cast<Map2*>(*mapp)->draw(*window);
    }

    player->draw(*window);

    hud->draw(*window);

    window->display();
}

