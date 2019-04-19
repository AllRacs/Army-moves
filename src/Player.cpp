#include "Player.h"

Player::Player()
{
    //ctor
    fuel = 0;
    points = 0;

    //animation


    //colision
    position = {150.f, 500.f};
    colision = new sf::RectangleShape();
    colision->setSize({100.f,100.f});
    colision->setPosition(position);
    colision->setOrigin({50.f,50.f});
    colision->setFillColor(sf::Color::Red);
    colision->setOrigin(colision->getGlobalBounds().width, colision->getGlobalBounds().height);

    std::cout << "Player created" << std::endl;
}

Player::~Player()
{
    //dtor
    delete colision;
}

void Player::controlPlayer(std::vector<sf::Sprite*> m)
{
    sf::Time time = c.getElapsedTime();
    //ŝstd::cout << time.asSeconds() << std::endl;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        //colision->setScale(-0.2, 0.2);
        colision->move({-vel * time.asMilliseconds(), 0});
        std::cout << colision->getPosition().x << " --- " << colision->getPosition().y << std::endl;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        //colision->setScale(-0.2, 0.2);
        colision->move({vel * time.asMilliseconds(), 0});
        std::cout << colision->getPosition().x << " +++ " << colision->getPosition().y << std::endl;

    }
    jump(m);
    c.restart();
}

void Player::jump(std::vector<sf::Sprite*> m)
{
    std::cout << m.size() << std::endl;
    sf::Time time = c.getElapsedTime();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        colision->move({0, -vel * time.asMilliseconds()});
    }
    else if(!colision->getGlobalBounds().intersects(m.at(0)->getGlobalBounds()))
    {
        colision->move({0, vel * time.asMilliseconds()});
    }
}

void Player::update(std::vector<sf::Sprite*> m)
{
    controlPlayer(m);
}

void Player::draw(sf::RenderWindow& w)
{
    //animation->draw(w);
    w.draw(*colision);
}

int Player::getFuel()
{
    return fuel;
}

int Player::getPoints()
{
    return points;
}
