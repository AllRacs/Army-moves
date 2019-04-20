#include "Animation.h"

Animation::Animation(sf::Texture spritesheet, float nx, float ny, float nw, float nh, int nmaxx)
{
    //ctor
    sprite = new sf::Sprite(spritesheet);
    x = nx;
    y = ny;
    w = nw;
    h = nh;
    nmax = nmaxx;
    sprite->setTextureRect(sf::IntRect(x, y, w, h));
}

Animation::~Animation()
{
    //dtor
    delete sprite;
}

void Animation::update()
{
    if(clock.getElapsedTime().asSeconds() >= 0.3)
    {
        clock.restart();
        if(pos++ < nmax)
        {
            sprite->setTextureRect(sf::IntRect(x*pos, y, w, h));
            sprite->setOrigin(w/2, h/2);
        }
        else if(pos == nmax)
        {
            pos = 0;
        }
    }
}

void Animation::draw(sf::RenderWindow& w)
{
    w.draw(*sprite);
}

void Animation::die()
{

}
