#include "Enemy.h"

Enemy::Enemy(sf::Texture& spritesheet, int n, int p, sf::Vector2f pos)
{
    //ctor


    phase = p;
    type = n;
    jumping = false;
    jumpUp = true;
    jumpDown = false;
    grav = 0;

    float x = pos.x - 20; // X coord to spawn at almost final of a bridge

    if(n==0)
    {
        //cars
        //std::cout << "NEW CAR" << std::endl;
        ammo = 0;
        dir = 1;
        //collision
        position = {x, 550.f};
        collision = new sf::RectangleShape();
        collision->setSize({100.f,100.f});
        collision->setPosition(position);
        collision->setOrigin({50.f,50.f});
        collision->setFillColor(sf::Color::Red);
        collision->setOrigin(collision->getGlobalBounds().width, collision->getGlobalBounds().height);

        //animation
        a_movement = new Animation(spritesheet, 63, 199, 159, 102, 2,
                                   {position.x - collision->getGlobalBounds().width/2 + 20, position.y - collision->getGlobalBounds().height/2}, 0.2, dir);
    }
    else if(n==1)
    {
        //helis
        //std::cout << "NEW HELI" << std::endl;
        ammo = 1;
        dir = 1;
        if(phase==1)
        {
            position = {1200.f, 200.f};
        }
        else
        {
            position = {10.f, 200.f};
        }

        //collision
        collision = new sf::RectangleShape();
        collision->setSize({100.f,100.f});
        collision->setPosition(position);
        collision->setOrigin({50.f,50.f});
        collision->setFillColor(sf::Color::Red);
        collision->setOrigin(collision->getGlobalBounds().width, collision->getGlobalBounds().height);

        //animation
        a_movement = new Animation(spritesheet, 1055, 208, 144, 82, 4,
                                   {position.x - collision->getGlobalBounds().width/2 + 20, position.y - collision->getGlobalBounds().height/2}, 0.2, dir);
    }
    else if(p==2 && n==2)
    {
        //jets
        std::cout << "NEW JET" << std::endl;
        ammo = 1;
    }
}

Enemy::~Enemy()
{
    //dtor
    delete collision;
    delete a_movement;
}

void Enemy::update(std::vector<sf::Sprite*> m)
{
    controlEnemy(m);
    a_movement->update();
}

void Enemy::draw(sf::RenderWindow& w)
{
    w.draw(*collision);
    a_movement->draw(w);
}

void Enemy::controlEnemy(std::vector<sf::Sprite*> m)
{
    sf::Time time = c.getElapsedTime();
    if(type==0)
    {
        //car movement
        collision->move({velCar * time.asMilliseconds(), 0});
        a_movement->movement({velCar * time.asMilliseconds(), 0});
        jump(m);

        c.restart();
    }
    else if(type==1)
    {
        int dir = 1;
        if(phase==2)
        {
            dir = -1;
        }

        //heli movement
        collision->move({dir * vel * time.asMilliseconds(), 0});
        a_movement->movement({dir * vel * time.asMilliseconds(), 0});
    }
    else if(type==2)
    {
        //jets movement
    }
    c.restart();
}

void Enemy::jump(std::vector<sf::Sprite*> m)
{
    sf::Time time = c.getElapsedTime();
    int down = 0;

    //check which is below
    for(int a = 0; a < m.size() && !jumping; a++)
    {
        if(m.at(a)->getGlobalBounds().left+20 <= collision->getPosition().x
           && m.at(a)->getGlobalBounds().left+100 >= collision->getPosition().x)
        {
            down = a;
            jumping = true;
            jumpUp = true;
            grav = 10;
            std::cout << "time 2 jump " << collision->getPosition().y << std::endl;
            cjump.restart();
            break;
        }
    }


    if(jumping)
    {
        if(jumpUp)
        {
            //move up
            //...
            collision->move({0.f, vel * time.asMilliseconds()});
            a_movement->movement({0.f, vel * time.asMilliseconds()});

            if(collision->getPosition().y <= 300)
            {
                jumpUp = false;
                jumpDown = true;
            }
        }
        if(jumpDown)
        {
            //move down
            //...
            collision->move({0.f, -vel * time.asMilliseconds()});
            a_movement->movement({0.f, -vel * time.asMilliseconds()});

            if(collision->getPosition().y >= 550)
            {
                jumpDown = false;
                jumping = false;
            }
        }
    }


    /*
    if(cjump.getElapsedTime().asSeconds() <= 2)
    {
        std::cout << "jumping" << std::endl;
        collision->move({0.f, vel * time.asMilliseconds()});
        a_movement->movement({0.f, vel * time.asMilliseconds()});
    }
    */
}

bool Enemy::shoot()
{
    bool res = false;
    if(ammo-- > 0)
    {
        res = true;
    }
    return res;
}

sf::RectangleShape* Enemy::getCollision()
{
    return collision;
}
