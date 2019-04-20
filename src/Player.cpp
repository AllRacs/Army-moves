#include "Player.h"

Player::Player(int p)
{
    //ctor
    fuel = 0;
    points = 0;

    if(p==1)
    {
        phase = p;
        //animation


        //collision
        position = {150.f, 500.f};
        collision = new sf::RectangleShape();
        collision->setSize({100.f,100.f});
        collision->setPosition(position);
        collision->setOrigin({50.f,50.f});
        collision->setFillColor(sf::Color::Red);
        collision->setOrigin(collision->getGlobalBounds().width, collision->getGlobalBounds().height);
    }
    else if(p==2)
    {
        phase = p;
        //animation


        //collision
        position = {800.f, 200.f};
        collision = new sf::RectangleShape();
        collision->setSize({100.f,100.f});
        collision->setPosition(position);
        collision->setOrigin({50.f,50.f});
        collision->setFillColor(sf::Color::Red);
        collision->setOrigin(collision->getGlobalBounds().width, collision->getGlobalBounds().height);
    }

    std::cout << "Player created" << std::endl;
}

Player::~Player()
{
    //dtor
    delete collision;
}

void Player::controlPlayer(std::vector<sf::Sprite*> m)
{
    sf::Time time = c.getElapsedTime();
    //ŝstd::cout << time.asSeconds() << std::endl;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        //collision->setScale(-0.2, 0.2);
        collision->move({-vel * time.asMilliseconds(), 0});
        std::cout << collision->getPosition().x << " --- " << collision->getPosition().y << std::endl;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        //collision->setScale(-0.2, 0.2);
        collision->move({vel * time.asMilliseconds(), 0});
        std::cout << collision->getPosition().x << " +++ " << collision->getPosition().y << std::endl;

    }
    if(phase==1)
    {
        jump(m);
    }
    else if(phase==2)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            collision->move({0, -vel * time.asMilliseconds()});
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            collision->move({0, vel * time.asMilliseconds()});
        }
    }

    c.restart();
}

void Player::jump(std::vector<sf::Sprite*> m)
{
    sf::Time time = c.getElapsedTime();
    int down = 0;

    //check which is below
    for(int a = 0; a < m.size(); a++)
    {
        if(m.at(a)->getGlobalBounds().left <= collision->getPosition().x
           && m.at(a)->getGlobalBounds().left+m.at(a)->getGlobalBounds().width >= collision->getPosition().x)
        {
            down = a;
        }
    }

    std::cout << "DOWN: " << down <<std::endl;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        collision->move({0, -vel * time.asMilliseconds()});
    }
    else if(!collision->getGlobalBounds().intersects(m.at(down)->getGlobalBounds()))
    {
        collision->move({0, vel * time.asMilliseconds()});
    }
}

bool Player::bulletCollision(std::vector<sf::Sprite*> bullets)
{
    bool res = false;
    //for each bullet -> if intersects -> res = true
    //...
    return res;
}

void Player::update(std::vector<sf::Sprite*> m)
{
    controlPlayer(m);
}

void Player::draw(sf::RenderWindow& w)
{
    //animation->draw(w);
    w.draw(*collision);
}

int Player::getFuel()
{
    return fuel;
}

int Player::getPoints()
{
    return points;
}
