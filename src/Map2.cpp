#include "Map2.h"

Map2::Map2(sf::Texture& spritesheetf)
{
    //ctor
    floor = std::vector<sf::Sprite*>{};

    ss_Floor = sf::IntRect(42,1222,1100,68);


    std::cout << "Map 2 created" << std::endl;
}

Map2::~Map2()
{
    //dtor
    while(floor.size() > 0)
    {
        delete floor.front();
        floor.erase(floor.begin());
    }

    while(enemies.size() > 0)
    {
        delete enemies.front();
        enemies.erase(enemies.begin());
    }

    while(bullets.size() > 0)
    {
        delete bullets.front();
        bullets.erase(bullets.begin());
    }
}

void Map2::update()
{

}

void Map2::draw(sf::RenderWindow& w)
{

}

void Map2::controlIA()
{

}

std::vector<sf::Sprite*> Map2::getFloor()
{
    return floor;
}

std::vector<Enemy*> Map2::getEnemies()
{
    return enemies;
}

std::vector<Bullet*> Map2::getBullets()
{
    return bullets;
}
