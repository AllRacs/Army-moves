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

    godMode = false;

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
    hud = new HUD(*spritesheet, state);
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
                else if(event->key.code == sf::Keyboard::G)
                {
                    GODMODE();
                }
                if(event->key.code == sf::Keyboard::Q)
                {
                    //shoot 1
                    std::cout << "SHOOT Q" << std::endl;
                    if(state==1)
                    {
                        dynamic_cast<Map1*>(*mapp)->playerShoot(0);
                    }
                }
                else if(event->key.code == sf::Keyboard::W)
                {
                    //shoot 2
                    std::cout << "SHOOT W" << std::endl;
                    if(state==1)
                    {
                        dynamic_cast<Map1*>(*mapp)->playerShoot(1);
                    }
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
            delete hud;
            state = s;
        }
        else if(state==2)
        {
            delete map2;
            delete hud;
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

void Game::endPhase1()
{
    if(state==1 && player->getFuel() < 500 && dynamic_cast<Map1*>(*mapp)->getHouse(player->getCollision()))
    {
        switchState(2);
    }
}


bool Game::bulletCollision()
{
    bool res = false;
    //for each bullet -> if intersects -> res = true and lives-- and reposition
    if(state==1)
    {
        int eSize = dynamic_cast<Map1*>(*mapp)->getBullets().size();
        if(eSize > 0)
        {
            for(int n = 0; n < eSize; n++)
            {
                if(player->getCollision()->getGlobalBounds().intersects(dynamic_cast<Map1*>(*mapp)->getBullets().at(n)->getCollision()->getGlobalBounds()))
                {
                    dynamic_cast<Map1*>(*mapp)->destroyBullet(n);
                    player->recieveDamage();
                    res = true;
                    break;
                }
            }
        }
    }

    return res;
}

bool Game::enemyCollision()
{
    bool res = false;
    //check collision with every enemy
    if(state==1)
    {
        int eSize = dynamic_cast<Map1*>(*mapp)->getEnemies().size();
        if(eSize > 0)
        {
            for(int n = 0; n < eSize; n++)
            {
                if(player->getCollision()->getGlobalBounds().intersects(dynamic_cast<Map1*>(*mapp)->getEnemies().at(n)->getCollision()->getGlobalBounds()))
                {
                    dynamic_cast<Map1*>(*mapp)->destroyEnemy(n);
                    player->recieveDamage();
                    res = true;
                    break;
                }
            }
        }
    }

    return res;
}

void Game::checkLives()
{
    if(player->getLives() == 0)
    {
        switchState(state);
    }
}

void Game::gameLoop()
{
    while(window->isOpen())
    {
        manageEvents();
        checkLives();
        update();
        draw();
        if(!godMode && (bulletCollision() || enemyCollision()))
        {
            player->recieveDamage();
        }
        endPhase1();
    }
}

void Game::update()
{
    if(state == 1)
    {
        //dynamic_cast<Map1*>(*mapp)->manageEvents(*window);
        player->update(dynamic_cast<Map1*>(*mapp)->getBridges());
        dynamic_cast<Map1*>(*mapp)->update(player->getFuel(), dynamic_cast<Map1*>(*mapp)->getBridges());
    }
    else if(state == 2)
    {
        player->update(dynamic_cast<Map2*>(*mapp)->getFloor());
        dynamic_cast<Map2*>(*mapp)->update();
    }
    hud->update(player->getFuel(), player->getPoints(), player->getLives());
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

void Game::GODMODE()
{
    godMode = !godMode;
    std::cout << "GODMODE: " << godMode << std::endl;
}
