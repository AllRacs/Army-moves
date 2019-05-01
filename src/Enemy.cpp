#include "Enemy.h"

Enemy::Enemy(sf::Texture& spritesheet, int n, int p, sf::Vector2f pos, bool showColl)
{
    //ctor


    phase = p;
    type = n;
    jumping = false;
    jumpUp = true;
    jumpDown = false;
    grav = 0;
    seeCollisions = showColl;
    jetBehavior = -1;
    jetState = 1;
    shootSignal = false;

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
        collision->setFillColor(sf::Color::Red);
        collision->setOrigin(collision->getGlobalBounds().width, collision->getGlobalBounds().height);

        //animation
        a_movement = new Animation(spritesheet, 1055, 208, 144, 82, 4,
                                   {position.x - collision->getGlobalBounds().width/2 + 20, position.y - collision->getGlobalBounds().height/2}, 0.2, dir);
    }
    else if(p==2 && n==2)
    {
        //jets
        //std::cout << "NEW JET" << std::endl;
        ammo = 1;
        dir = 1;

        srand(time(NULL));
        int n = rand() % 2;
        if(n < 1)
        {
            position = {0.f, pos.y};   //jet starts at left
            jetBehavior = 1;
        }
        else
        {
            position = {1100.f, pos.y};   //jet starts at right
            jetBehavior = 2;
            dir = -1;
        }

        //collision
        collision = new sf::RectangleShape();
        collision->setSize({100.f,100.f});
        collision->setPosition(position);
        collision->setFillColor(sf::Color::Red);
        collision->setOrigin(collision->getGlobalBounds().width, collision->getGlobalBounds().height);

        //animation
        a_movement = new Animation(spritesheet, 1372, 331, 187, 107, 1,
                                   {position.x - collision->getGlobalBounds().width/2 + 20, position.y - collision->getGlobalBounds().height/2}, 0.2, dir);
    }
    else if(p==2 && n==3)
    {
        //antiaircraft
        dir = 1;
        //std::cout << "NEW ANTI AIR" << std::endl;
        ammo = 2;
        collision = new sf::RectangleShape();
        collision->setSize({160.f, 70.f});
        collision->setOrigin({80.f, 30.f});
        collision->setPosition(pos);
        collision->setFillColor(sf::Color::Red);

        //animation
        a_movement = new Animation(spritesheet, 74, 1084, 222, 46, 4,
                                   {collision->getPosition().x, collision->getPosition().y}, 0.5, dir);
    }
}

Enemy::~Enemy()
{
    //dtor
    delete collision;
    delete a_movement;
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

        //heli movement
        collision->move({dir * vel * time.asMilliseconds(), 0});
        a_movement->movement({dir * vel * time.asMilliseconds(), 0});
    }
    else if(type==2)
    {
        //jets movement
        if(jetBehavior == 1)
        {
            // script: 3 states -> (1) moveBshoot, (2) shoot, (3) moveAshoot
            // if(moveBshoot) move right, else if(shoot) dont move, else if(moveAshoot) move left
            if(jetState == 1)
            {
                collision->move({-dir * vel * time.asMilliseconds(), 0});
                a_movement->movement({-dir * vel * time.asMilliseconds(), 0});
                if(collision->getPosition().x >= 200)
                {
                    jetState = 2;
                    wait2shoot.restart(); // WARNING if causes troubles move up w/ ->move calls
                }
            }
            else if(jetState == 2)
            {
                if(wait2shoot.getElapsedTime().asSeconds() >= 1.5)
                {
                    //signal shoot & state 3
                    shootSignal = true;
                    jetState = 3;
                    dir = 1;
                    a_movement->changeDirection();
                }
            }
            else if(jetState == 3)
            {
                collision->move({dir * vel * time.asMilliseconds(), 0});
                a_movement->movement({dir * vel * time.asMilliseconds(), 0});
            }
        }
        else if(jetBehavior == 2)
        {
            // script: 3 states -> (1) moveBshoot, (2) shoot, (3) moveAshoot
            // if(moveBshoot) move right, else if(shoot) dont move, else if(moveAshoot) move left
            if(jetState == 1)
            {
                collision->move({-dir * vel * time.asMilliseconds(), 0});
                a_movement->movement({-dir * vel * time.asMilliseconds(), 0});
                if(collision->getPosition().x <= 200)
                {
                    jetState = 2;
                    a_movement->changeDirection();
                    wait2shoot.restart(); // WARNING if causes troubles move up w/ ->move calls
                }
            }
            else if(jetState == 2)
            {
                if(wait2shoot.getElapsedTime().asSeconds() >= 1.5)
                {
                    //signal shoot & state 3
                    a_movement->changeDirection();
                    shootSignal = true;
                    jetState = 3;
                    dir = 1;
                }
            }
            else if(jetState == 3)
            {
                collision->move({dir * vel * time.asMilliseconds(), 0});
                a_movement->movement({dir * vel * time.asMilliseconds(), 0});
            }
        }
    }
    else if(type==3)
    {
        collision->move({velAC * time.asMilliseconds(), 0});
        a_movement->movement({velAC * time.asMilliseconds(), 0});
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
            grav = 1;
            cjump.restart();
            break;
        }
    }


    if(jumping)
    {
        if(jumpUp)
        {
            //move up
            collision->move({0.f, (vel - 0.3) * time.asMilliseconds() * grav});
            a_movement->movement({0.f, (vel - 0.3) * time.asMilliseconds() * grav});
            grav -= 0.01;
            if(collision->getPosition().y <= 325)
            {
                jumpUp = false;
                jumpDown = true;
            }
        }
        if(jumpDown)
        {
            //move down
            collision->move({0.f, -(vel - 0.3) * time.asMilliseconds() * grav});
            a_movement->movement({0.f, -(vel - 0.3) * time.asMilliseconds() * grav});
            grav += 0.01;
            if(collision->getPosition().y >= 550)
            {
                jumpDown = false;
                jumping = false;
            }
        }
    }
}

bool Enemy::shoot()
{
    bool res = false;
    if(type != 2 && ammo-- > 0)
    {
        res = true;
    }
    else if(type == 2 && ammo-- > 0)
    {
        res = true;
        shootSignal = false;
    }
    return res;
}

void Enemy::update(std::vector<sf::Sprite*> m)
{
    controlEnemy(m);
    a_movement->update();
}

void Enemy::draw(sf::RenderWindow& w)
{
    if(seeCollisions)
        w.draw(*collision);
    a_movement->draw(w);
}

sf::RectangleShape* Enemy::getCollision()
{
    return collision;
}

int Enemy::getType()
{
    return type;
}

void Enemy::showCollisions()
{
    seeCollisions = !seeCollisions;
}
