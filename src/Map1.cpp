#include "Map1.h"

Map1::Map1(sf::Texture& spritesheet)
{
    //ctor
    std::cout << "Map 1 created" << std::endl;

    enemies = std::vector<Enemy>{};

    /*defBridges = new sf::Sprite[4];
    for(int a = 0; a < 4; a++)
    {
        defBridges[a] = sf::Sprite(spritesheet);
        switch(a)
        {
            case 0:
                defBridges[a].setTextureRect(sf::IntRect(56,858,320,112));
                break;
            case 1:
                defBridges[a].setTextureRect(sf::IntRect(56,858,320,112));
                break;
            case 2:
                defBridges[a].setTextureRect(sf::IntRect(56,858,320,112));
                break;
            case 3:
                defBridges[a].setTextureRect();
                break;
        }
    }*/

    bridges = std::vector<sf::Sprite*>{};

    for(int a = 0; a < 3; a++)
    {
        //insert 3 new bridges sprites
        bridges.push_back(new sf::Sprite());
        bridges.at(bridges.size())->setTextureRect(sf::IntRect(56,858,320,112));
    }

}

Map1::~Map1()
{
    //dtor

}

void Map1::newBridge()
{
    //delete head
    //...
    //push_back bridge sprite
}

void Map1::controlIA()
{
    //move bridges
    //...
    //move cars/heli
    //...
    //make jump (cars)
    //...
    //make shoot (heli)
}

void Map1::update()
{
    controlIA();
}

void Map1::draw(sf::RenderWindow& w)
{
    //draw bridges
    //...
    //draw enemies
    //...
}

std::vector<sf::Sprite*> Map1::getBridges()
{
    return bridges;
}
