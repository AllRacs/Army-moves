#include "Bullet.h"

Bullet::Bullet(sf::Texture& spritesheet,int n, int p, int d, sf::Vector2f pos)
{
    //ctor
    type = n; //sprite: bullet (0) or rocket (1)
    phase = p;
    dir = d;

    bullet = new sf::Sprite(spritesheet);
    if(n==0)
    {
        //sprite: bullet
        bullet->setTextureRect(sf::IntRect(527,247,21,21));
    }
    else if(n==1)
    {
        //sprite: rocket
        bullet->setTextureRect(sf::IntRect(535,246,54,21));
    }

    bullet->setPosition(pos);
}

Bullet::~Bullet()
{
    //dtor
    delete bullet;
}

void Bullet::update()
{
    sf::Time time = c.getElapsedTime();

    // dir: 1 => up and right, 2 => right straight, 3 => down, 4 => left and down, 5 => straight left
    switch(dir)
    {
        case 1:
            bullet->move(vel * time.asMilliseconds(), -vel * 3/4 * time.asMilliseconds());
            break;
        case 2:
            break;
            bullet->move(vel * time.asMilliseconds(), 0);
        case 3:
            bullet->move(0, vel * 3/4 * time.asMilliseconds());
            break;
        case 4:
            bullet->move(-vel * time.asMilliseconds(), vel * 2/4 * time.asMilliseconds());
            break;
        case 5:
            bullet->move(-vel * time.asMilliseconds(), 0);
            break;
    }
    c.restart();
}

void Bullet::draw(sf::RenderWindow& w)
{
    w.draw(*bullet);
}

sf::Sprite* Bullet::getCollision()
{
    return bullet;
}
