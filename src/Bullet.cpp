#include "Bullet.h"

Bullet::Bullet(sf::Texture& spritesheet,int n, int p, int d, sf::Vector2f pos)
{
    //ctor
    type = n; //sprite: bullet (0) or rocket (1)
    phase = p;
    dir = d;

    bullet = new sf::Sprite(spritesheet);
    scale = {1.006f, 1.534f};
    bullet->setScale({scale.x, scale.y});
    if(n == 0)
    {
        //sprite: bullet
        bullet->setTextureRect(sf::IntRect(520,245,21,21));
    }
    else if(n == 1)
    {
        //sprite: rocket
        bullet->setTextureRect(sf::IntRect(400,72,54,36));
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
        case 1:     // dir: 1 => up and right
            if(type == 1 && bullet->getPosition().y >= 100)
            {
                bullet->move(vel * time.asMilliseconds(), 0);
            }
            else
            {
                bullet->move(vel * time.asMilliseconds(), -vel * time.asMilliseconds());
            }
            break;
        case 2:     //dir: 2 => right straight
            bullet->move(vel * time.asMilliseconds(), 0);
            break;
        case 3:     //dir: 3 => down
            bullet->move(0, vel * 3/4 * time.asMilliseconds());
            break;
        case 4:     //dir: 4 => left and down
            bullet->move(-vel * time.asMilliseconds(), vel * 2/4 * time.asMilliseconds());
            break;
        case 5:     //dir: 5 => straight left
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
