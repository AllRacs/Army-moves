#include "Enemy.h"

Enemy::Enemy(int n, int p, sf::Vector2f pos)
{
    //ctor


    phase = p;

    type = n;
    flagJump = false;

    float x = pos.x - 20; // X coord to spawn at almost final of a bridge

    if(n==0)
    {
        //cars
        std::cout << "NEW CAR" << std::endl;
        ammo = 0;


        //collision
        position = {x, 550.f};
        collision = new sf::RectangleShape();
        collision->setSize({100.f,100.f});
        collision->setPosition(position);
        collision->setOrigin({50.f,50.f});
        collision->setFillColor(sf::Color::Red);
        collision->setOrigin(collision->getGlobalBounds().width, collision->getGlobalBounds().height);

        //animation



    }
    else if(n==1)
    {
        //helis
        std::cout << "NEW HELI" << std::endl;
        ammo = 1;

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
}

void Enemy::update(std::vector<sf::Sprite*> m)
{
    controlEnemy(m);
}

void Enemy::draw(sf::RenderWindow& w)
{
    w.draw(*collision);
}

void Enemy::controlEnemy(std::vector<sf::Sprite*> m)
{
    sf::Time time = c.getElapsedTime();
    if(type==0)
    {
        //car movement
        collision->move({velCar * time.asMilliseconds(), 0});
        //jump(m);

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
    bool time2jump = false;

    //check which is below
    for(int a = 0; a < m.size(); a++)
    {
        if(m.at(a)->getGlobalBounds().left <= collision->getPosition().x
           && m.at(a)->getGlobalBounds().left+30 >= collision->getPosition().x)
        {
            down = a;
            time2jump = true;
        }
    }

    if(time2jump && collision->getPosition().y>= 540 && collision->getPosition().y<=560)
    {
        flagJump = true;
        baseJump = collision->getPosition().y;
        cjump.restart();
        grav = 0;
    }
    else if(collision->getPosition().y > 560)
    {
        float y = (velCar*0.2) * time.asMilliseconds();
        y += grav;
        grav += 0.16;
        collision->move({0, y});
    }
    else if(!flagJump && !collision->getGlobalBounds().intersects(m.at(down)->getGlobalBounds()))
    {
        float y = (velCar*0.2) * time.asMilliseconds();
        y += grav;
        grav += 0.16;
        collision->move({0, y});
    }
    else if(collision->getGlobalBounds().intersects(m.at(down)->getGlobalBounds()))
    {
        grav = 0;
    }

    if(flagJump)
    {
        if(collision->getPosition().y <= 260)
        {
            flagJump = false;
            grav = 0;
        }
        float y = -(velCar*3) * time.asMilliseconds();
        grav += 0.16;
        y += grav;
        collision->move({0, y});
    }
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
