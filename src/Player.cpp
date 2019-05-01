#include "Player.h"

Player::Player(sf::Texture& spritesheet, int p)
{
    //ctor
    fuel = 5000;
    points = 0;
    lives = 5;
    grav = 0;
    flagJump = false;
    fin = false;
    seeCollisions = false;
    baseJump = 0;
    if(p==1)
    {
        phase = p;
        dir = 1;
        //collision
        position = {150.f, 500.f};
        collision = new sf::RectangleShape();
        collision->setSize({100.f,100.f});
        collision->setPosition(position);
        collision->setOrigin({50.f,0.f});
        collision->setFillColor(sf::Color::Red);
        collision->setOrigin(collision->getGlobalBounds().width, collision->getGlobalBounds().height);

        //animation
        a_movement = new Animation(spritesheet, 63, 50, 151, 82, 2, {position.x - collision->getGlobalBounds().width/2, position.y - collision->getGlobalBounds().height/2}, 0.2, dir);
    }
    else if(p==2)
    {
        phase = p;
        dir = 1;
        //collision
        position = {800.f, 200.f};
        collision = new sf::RectangleShape();
        collision->setSize({80.f,80.f});
        collision->setPosition(position);
        collision->setOrigin({40.f,0.f});
        collision->setFillColor(sf::Color::Red);
        collision->setOrigin(collision->getGlobalBounds().width, collision->getGlobalBounds().height);

        //animation
        a_movement = new Animation(spritesheet, 1055, 208, 144, 82, 4, {position.x - collision->getGlobalBounds().width/2 + 20, position.y - collision->getGlobalBounds().height/2}, 0.1, dir);
        a_forward = new Animation(spritesheet, 1055, 92, 144, 82, 4, {position.x - collision->getGlobalBounds().width/2 + 20, position.y - collision->getGlobalBounds().height/2}, 0.1, dir);
    }

    std::cout << "Player created" << std::endl;
}

Player::~Player()
{
    //dtor
    delete collision;
    delete a_movement;
    if(phase==2)
            delete a_forward;
}

void Player::controlPlayer(std::vector<sf::Sprite*> m)
{
    sf::Time time = c.getElapsedTime();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && collision->getPosition().x >= 125)
    {
        collision->move({-vel * time.asMilliseconds(), 0});
        a_movement->movement({-vel * time.asMilliseconds(), 0});
        if(phase==2)
            a_forward->movement({-vel * time.asMilliseconds(), 0});
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && collision->getPosition().x <= 970)
    {
        collision->move({vel * time.asMilliseconds(), 0});
        a_movement->movement({vel * time.asMilliseconds(), 0});
        if(phase==2)
            a_forward->movement({vel * time.asMilliseconds(), 0});
    }
    if(phase==1)
    {
        jump(m);
    }
    else if(phase==2)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && collision->getPosition().y >= 140)
        {
            collision->move({0, -vel * time.asMilliseconds()});
            a_movement->movement({0, -vel * time.asMilliseconds()});
            if(phase==2)
                a_forward->movement({0, -vel * time.asMilliseconds()});
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && collision->getPosition().y <= 630)
        {
            collision->move({0, vel * time.asMilliseconds()});
            a_movement->movement({0, vel * time.asMilliseconds()});
            if(phase==2)
                a_forward->movement({0, vel * time.asMilliseconds()});
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

    //std::cout << collision->getPosition().y << std::endl;

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
        a_movement->movement({0, y});
        if(phase==2)
            a_forward->movement({0, y});
    }
    else if(!flagJump && !collision->getGlobalBounds().intersects(m.at(down)->getGlobalBounds()))
    {
        float y = (vel*0.2) * time.asMilliseconds();
        y += grav;
        grav += 0.16;
        //std::cout << grav << std::endl;
        collision->move({0, y});
        a_movement->movement({0, y});
        if(phase==2)
            a_forward->movement({0, y});
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
        float y = -(vel*3) * time.asMilliseconds();
        grav += 0.16;
        y += grav;
        collision->move({0, y});
        a_movement->movement({0, y});
        if(phase==2)
            a_forward->movement({0, y});
    }
}

void Player::reposition()
{
    grav = 0;

    //select best position to respawn
    // sf::Vector2f v ...

    sf::Vector2f v;
    if(phase==1)
        v = {150.f,300.f};
    else if(phase==2)
        v = {800.f, 200.f};

    a_movement->reposition({v.x - collision->getGlobalBounds().width/2, v.y - collision->getGlobalBounds().height/2});
    if(phase==2)
    {
        a_movement->reposition({v.x - collision->getGlobalBounds().width/3 + 5, v.y - collision->getGlobalBounds().height/2});
        a_forward->reposition({v.x - collision->getGlobalBounds().width/3 + 5, v.y - collision->getGlobalBounds().height/2});
    }
    collision->setPosition(v);
}

void Player::recieveDamage()
{
    reposition();
    lives--;
}

void Player::updatePoints()
{
    if(!fin && cpoints.getElapsedTime().asSeconds() >= 1)
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
    if(!fin && cfuel.getElapsedTime().asSeconds() >= 0.1)
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
    a_movement->update();
    if(phase==2)
    {
        a_forward->update();
        if(fuel <= 300)
        {
            fin = true;
        }
    }
    if(collision->getPosition().y >= 680)
    {
        recieveDamage();
    }
}

void Player::draw(sf::RenderWindow& w)
{
    if(seeCollisions)
        w.draw(*collision);
    if(phase==2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        a_forward->draw(w);
    }
    else
    {
        a_movement->draw(w);
    }
}

void Player::showCollisions()
{
    seeCollisions = !seeCollisions;
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

sf::RectangleShape* Player::getCollision()
{
    return collision;
}
