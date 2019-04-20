#include "Map1.h"

Map1::Map1(sf::Texture& spritesheet)
{
    //ctor
    std::cout << "Map 1 created" << std::endl;

    enemies = std::vector<Enemy>{};

    bridges = std::vector<sf::Sprite*>{};

    ss_bridges[0] = sf::IntRect(56,858,320,112);
    ss_bridges[1] = sf::IntRect(56,858,320,112);
    ss_bridges[2] = sf::IntRect(56,858,320,112);
    ss_bridges[3] = sf::IntRect(56,858,320,112);


    for(int a = 0; a < 3; a++)
    {
        //insert 3 new bridges sprites
        bridges.push_back(new sf::Sprite(spritesheet));
        bridges.back()->setTextureRect(ss_bridges[a]);
        bridges.back()->setPosition({100.f+400*a, 550.f});
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
    for(int a = 0; a < bridges.size(); a++)
    {
        w.draw(*bridges.at(a));
    }
    //draw enemies
    //...

}

std::vector<sf::Sprite*> Map1::getBridges()
{
    return bridges;
}
