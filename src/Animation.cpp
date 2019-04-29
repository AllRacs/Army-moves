#include "Animation.h"

Animation::Animation(sf::Texture& spritesheet, float nx, float ny, float nw, float nh, int nmaxx, sf::Vector2f ini, float v, int dir)
{
    scale = {dir * 1.006f, 1.534f}; //dir -1 (left) o 1 (right)
    pos = 0;
    //ctor
    x = nx;
    y = ny;
    w = nw;
    h = nh;
    nmax = nmaxx;
    vel = v;
    sprite = new sf::Sprite(spritesheet);
    sprite->setScale(scale);
    sprite->setOrigin({w/2, h/2});
    sprite->setPosition(ini);
    sprite->setTextureRect(sf::IntRect(x, y, w, h));
}

Animation::~Animation()
{
    //dtor
    delete sprite;
}

void Animation::update()
{
    if(clock.getElapsedTime().asSeconds() >= vel)
    {
        clock.restart();
        if(pos < nmax)
        {
            sprite->setTextureRect(sf::IntRect(x + w * pos++, y, w, h));
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

void Animation::movement(sf::Vector2f m)
{
    sprite->move(m);
}

void Animation::reposition(sf::Vector2f v)
{
    sprite->setPosition(v);
}
