#include "HUD.h"

HUD::HUD(sf::Texture& spritesheet, int p)
{
    //ctor
    layout.setTexture(spritesheet);
    layout.setTextureRect(sf::IntRect(1430,862,1010,666));
    layout.setScale(1.006f, 1.534f);
    layout.setPosition(0.f, 0.f);

    iconplayer = new sf::Sprite(spritesheet);
    if(p==1)
    {
        iconplayer->setTextureRect(sf::IntRect());
    }
    else if(p==2)
    {
        iconplayer->setTextureRect(sf::IntRect());
    }


    pixelFont = new sf::Font;
    if(!pixelFont->loadFromFile("fonts/VCR.ttf"))
    {
        std::cout << "Font not found" << std::endl;
    }

    ipoints = 0;
    ifuel = 0;
    ilives = 0;

    points = new sf::Text;
    points->setFont(*pixelFont);
    points->setPosition(450.f, 860.f);
    points->setString("POINTS");
    points->setCharacterSize(36);

    fuel = new sf::Text;
    fuel->setFont(*pixelFont);
    fuel->setPosition(800.f, 860.f);
    fuel->setString("FUEL");
    fuel->setCharacterSize(36);

    lives = new sf::Text;
    lives->setFont(*pixelFont);
    lives->setPosition(62.f, 810.f);
    lives->setString("LIVES");
    lives->setCharacterSize(36);

    std::cout << "HUD created" << std::endl;
}

HUD::~HUD()
{
    //dtor
    delete iconplayer;
    delete pixelFont;
    delete points;
    delete fuel;
}

void HUD::update(int f, int p, int l)
{
    updateFuel(f);
    updatePoints(p);
    updateLives(l);
}

void HUD::updatePoints(int p)
{
    ipoints = p;
    points->setString(std::to_string(ipoints));
}

void HUD::updateFuel(int f)
{
    ifuel = f;
    fuel->setString(std::to_string(ifuel));
}

void HUD::updateLives(int l)
{
    ilives = l;
    lives->setString(std::to_string(ilives));
}

void HUD::draw(sf::RenderWindow& w)
{
    w.draw(layout);
    w.draw(*points);
    w.draw(*fuel);
    w.draw(*lives);
    w.draw(*iconplayer);
}

int HUD::getPoints()
{
    return ipoints;
}

int HUD::getFuel()
{
    return ifuel;
}
