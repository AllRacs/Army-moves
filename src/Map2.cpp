#include "Map2.h"

Map2::Map2(sf::Texture& spritesheet)
{
    //ctor

    //SETTING FLOOR
    floor = std::vector<sf::Sprite*>{};
    cFloor.restart();

    //SETTING ENEMIES
    enemies = std::vector<Enemy*>{};

    //SETTING BULLETS
    bullets = std::vector<Bullet*>{};
    pBullets = std::vector<Bullet*>{};

    fin = false;
    showHeliport = false;
    sp = &spritesheet;
    seeCollisions = false;

    ss_Floor = sf::IntRect(44,1222,1092,68);
    for(int a = 0; a < 2; a++)
    {
        floor.push_back(new sf::Sprite(spritesheet));
        floor.at(a)->setTextureRect(ss_Floor);
        if(floor.size() > 1)
        {
            floor.at(a)->setPosition({0.f - floor.back()->getPosition().x - floor.back()->getGlobalBounds().width, 585.f});
        }
        else if(floor.size() == 1)
        {
            floor.at(a)->setPosition({0.f, 585.f});
        }
    }

    heliport = new sf::Sprite(*sp);
    heliport->setTextureRect(sf::IntRect(1066,917,324,28));
    heliport->setPosition({-320.f, 600.f});

    newEnemyAC();

    std::cout << "Map 2 created" << std::endl;
}

Map2::~Map2()
{
    //dtor
    while(floor.size() > 0)
    {
        delete floor.front();
        floor.erase(floor.begin());
    }

    while(enemies.size() > 0)
    {
        delete enemies.front();
        enemies.erase(enemies.begin());
    }

    while(bullets.size() > 0)
    {
        delete bullets.front();
        bullets.erase(bullets.begin());
    }
    delete heliport;
}

void Map2::newFloor()
{
    delete floor.front();
    floor.erase(floor.begin());

    floor.push_back(new sf::Sprite(*sp));
    floor.back()->setTextureRect(ss_Floor);
    floor.back()->setPosition({floor.at(floor.size()-1)->getPosition().x - floor.at(floor.size()-1)->getGlobalBounds().width - 90, 585.f});
}

void Map2::controlFloor(int fuel)
{
    sf::Time time = cFloor.getElapsedTime();
    if(fuel <= 300)
    {
        fin = true;
    }
    if(!fin && fuel <= 500)
    {
        showHeliport = true;
        heliport->move({0.2 * time.asMilliseconds(), 0});
    }
    for(int a = 0; a < floor.size() && !fin; a++)
    {
        floor.at(a)->move({0.2 * time.asMilliseconds(), 0});
        if(floor.at(a)->getPosition().x >= 980)
        {
            newFloor();
            break;
        }
    }
    cFloor.restart();
}

void Map2::newEnemyAC()
{
    enemies.push_back(new Enemy(*sp, 3, 2, {-80.f, 625.f}, seeCollisions));
}

void Map2::manageACbullets()
{
    if(cspawnBullets.getElapsedTime().asSeconds() >= 1.5 && enemies.size() > 0 && enemies.back()->shoot())
    {
        bullets.push_back(new Bullet(*sp, 0, 2, 1, {enemies.back()->getCollision()->getPosition()}));
        cspawnBullets.restart();
    }
    for(int a = 0; a < bullets.size(); a++)
    {
        bullets.at(a)->update();
        if(bullets.at(a)->getCollision()->getPosition().x >= 1000 || bullets.at(a)->getCollision()->getPosition().y <= 10)
        {
            delete bullets.at(a);
            bullets.erase(bullets.begin()+a);
        }
    }
}

void Map2::destroyBullet(int n)
{
    delete bullets.at(n);
    bullets.erase(bullets.begin()+n);
}

void Map2::controlIA(int fuel)
{
    manageACbullets();
    if(fuel >= 700 )
    {
        if(spawnAntiair.getElapsedTime().asSeconds() >= 7)
        {
            newEnemyAC();
            spawnAntiair.restart();
        }
    }

    for(int a = 0; a < enemies.size(); a++)
    {
        enemies.at(a)->update(floor);
        if(enemies.at(a)->getCollision()->getPosition().x >= 1090)
        {
            delete enemies.at(a);
            enemies.erase(enemies.begin()+a);
            break;
        }
    }
}

void Map2::update(int fuel)
{
    controlFloor(fuel);
    controlIA(fuel);
}

void Map2::draw(sf::RenderWindow& w)
{
    for(int a = 0; a < floor.size(); a++)
    {
        w.draw(*floor.at(a));
    }
    for(int a = 0; a < enemies.size(); a++)
    {
        enemies.at(a)->draw(w);
    }
    for(int a = 0; a < bullets.size(); a++)
    {
        bullets.at(a)->draw(w);
    }
    if(showHeliport)
    {
        w.draw(*heliport);
    }
}

void Map2::showCollisions()
{
    for(int a = 0; a < enemies.size(); a++)
    {
        enemies.at(a)->showCollisions();
    }
    seeCollisions = !seeCollisions;
}

std::vector<sf::Sprite*> Map2::getFloor()
{
    return floor;
}

std::vector<Enemy*> Map2::getEnemies()
{
    return enemies;
}

std::vector<Bullet*> Map2::getBullets()
{
    return bullets;
}
