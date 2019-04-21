#include "Player.h"

Player::Player(int p)
{
    //ctor
    fuel = 5000;
    points = 0;
    lives = 5;
    grav = 0;
    flagJump = false;
    baseJump = 0;

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
        //std::cout << collision->getPosition().x << " --- " << collision->getPosition().y << std::endl;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        //collision->setScale(-0.2, 0.2);
        collision->move({vel * time.asMilliseconds(), 0});
        //std::cout << collision->getPosition().x << " +++ " << collision->getPosition().y << std::endl;

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

    std::cout << collision->getPosition().y << std::endl;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && collision->getPosition().y>= 540 && collision->getPosition().y<=560)
    {
        flagJump = true;
        baseJump = collision->getPosition().y;
        cjump.restart();
        grav = 0;
    }
    else if(collision->getPosition().y > 560)
    {
        float y = (vel*0.2) * time.asMilliseconds();
        y += grav;
        grav += 0.16;
        //std::cout << grav << std::endl;
        collision->move({0, y});
    }
    else if(!flagJump && !collision->getGlobalBounds().intersects(m.at(down)->getGlobalBounds()))
    {
        float y = (vel*0.2) * time.asMilliseconds();
        y += grav;
        grav += 0.16;
        //std::cout << grav << std::endl;
        collision->move({0, y});
    }
    else if(collision->getGlobalBounds().intersects(m.at(down)->getGlobalBounds()))
    {
        grav = 0;
    }

    if(flagJump)
    {
        if(collision->getPosition().y <= 250)
        {
            flagJump = false;
            grav = 0;
        }
        float y = -(vel*3) * time.asMilliseconds();
        grav += 0.16;
        y += grav;
        collision->move({0, y});
    }
}

void Player::reposition()
{
    grav = 0;

    //select best position to respawn
    // sf::Vector2f v ...
    sf::Vector2f v = {150.f,300.f};
    collision->setPosition(v);

    //animation->reposition(v);
}

void Player::recieveDamage()
{
    lives--;
}

void Player::updatePoints()
{
    if(cpoints.getElapsedTime().asSeconds() >= 1)
    {
        points += 100;
        cpoints.restart();
    }
}

void Player::updatePoints(int n)
{
    points += n;
}

void Player::updateFuel()
{
    if(cfuel.getElapsedTime().asSeconds() >= 0.2)
    {
        fuel -= 10;
        cfuel.restart();
    }
}

void Player::update(std::vector<sf::Sprite*> m)
{
    controlPlayer(m);
    updatePoints();
    updateFuel();

    if(collision->getPosition().y >= 680)
    {
        reposition();
        recieveDamage();
    }
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

int Player::getLives()
{
    return lives;
}
