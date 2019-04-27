#include "Map1.h"

Map1::Map1(sf::Texture& spritesheet)
{
    //ctor
    std::cout << "Map 1 created" << std::endl;
    sp = &spritesheet;
    houseEnd = false;

    //SETTING ENEMIES
    enemies = std::vector<Enemy*>{};

    //SETTING BULLETS
    bullets = std::vector<Bullet*>{};
    pBullets = std::vector<Bullet*>{};

    //SETTING BRIDGES
    bridges = std::vector<sf::Sprite*>{};

    ss_bridges[0] = sf::IntRect(44,385,1131,105);    // 2 arcos
    ss_bridges[1] = sf::IntRect(57,634,705,105);    // 1 arco
    ss_bridges[2] = sf::IntRect(57,861,318,105);    // 1/2 arco
    ss_bridges[3] = sf::IntRect(801,634,1384,105);    // 3 arcos


    for(int a = 0; a < 3; a++)
    {
        //insert 3 new bridges sprites
        bridges.push_back(new sf::Sprite(spritesheet));
        bridges.back()->setTextureRect(ss_bridges[a]);
        if(bridges.size() > 1)
        {
            bridges.back()->setPosition({bridges.at(a-1)->getPosition().x
                                        + bridges.at(a-1)->getGlobalBounds().width
                                        + 150, 550.f});
            newEnemy(a);
        }
        else
        {
            std::cout << "first bridge" << std::endl;
            bridges.back()->setPosition({100.f, 550.f});
        }
        //std::cout << bridges.at(a)->getPosition().x << " --- " << bridges.at(a)->getGlobalBounds().width << std::endl;
    }

}

Map1::~Map1()
{
    //dtor
    while(bridges.size() > 0)
    {
        delete bridges.front();
        bridges.erase(bridges.begin());
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
    if(houseEnd)
        delete house;
}

void Map1::newBridge(bool fin)
{
    if(!fin)
    {
        delete bridges.front();
        bridges.erase(bridges.begin());

        srand(time(NULL));
        int n = rand() % 3;

        bridges.push_back(new sf::Sprite(*sp));
        bridges.back()->setTextureRect(ss_bridges[n]);
        if(bridges.size() > 1)
        {
            bridges.back()->setPosition({bridges.at(bridges.size()-2)->getPosition().x
                                        + bridges.at(bridges.size()-2)->getGlobalBounds().width
                                        + 150, 550.f});
        }

        newEnemy(0);

    }
    else if(fin)
    {
        houseEnd = true;

        bridges.push_back(new sf::Sprite(*sp));
        bridges.back()->setTextureRect(ss_bridges[3]);
        if(bridges.size() > 1)
        {
            bridges.back()->setPosition({bridges.at(bridges.size()-2)->getPosition().x
                                        + bridges.at(bridges.size()-2)->getGlobalBounds().width
                                        + 150, 550.f});
        }

        house = new sf::Sprite(*sp);
        house->setTextureRect(sf::IntRect(1590,490,190,102));
        house->setOrigin(190/2,102);
        house->setPosition({bridges.at(bridges.size()-2)->getPosition().x
                                        + bridges.at(bridges.size()-2)->getGlobalBounds().width
                                        + 1200, 550.f});
    }
}

void Map1::newEnemy(int n)
{
    if(n == 0)
    {
        sf::Vector2f pos = {bridges.back()->getPosition().x + bridges.back()->getGlobalBounds().width, bridges.back()->getPosition().y};
        enemies.push_back(new Enemy(0, 1, pos));
    }
    if(n == 1)
    {
        enemies.push_back(new Enemy(1, 1, {0.f, 0.f}));
    }
}

void Map1::destroyEnemy(int n)
{
    delete enemies.at(n);
    enemies.erase(enemies.begin()+n);
}

void Map1::destroyBullet(int n)
{
    delete bullets.at(n);
    bullets.erase(bullets.begin()+n);
}

void Map1::playerShoot(int n)
{
    if(n==0)
    {
        //Q shoot
    }
    else if(n==1)
    {
        //W shoot
    }
}

void Map1::hitEnemies()
{
    //if a pBullet intersects with some enemy --> destroyEnemy(n) and destroyPBullet(m)
    for(int a = 0; a < pBullets.size(); a++)
    {
        for(int b = 0; b < enemies.size(); b++)
        {
            if(pBullets.at(a)->getCollision().getGlobalBounds().intersects(enemies.at(b)->getCollision()->getGlobalBounds()))
            {
                std::cout << "ENEMY SHOULD DIE" << std::endl;
            }
        }
    }
}

void Map1::destroyPBullet(int n)
{
    delete pBullets.at(n);
    pBullets.erase(pBullets.begin()+n);
}

void Map1::controlIA()
{

    if(cHeliSpawn.getElapsedTime().asSeconds() >= 5)
    {
        newEnemy(1);
        cHeliSpawn.restart();
    }

    for(int a = 0; a < enemies.size(); a++)
    {
        if(enemies.at(a)->getCollision()->getPosition().x >= 500 && enemies.at(a)->getCollision()->getPosition().x <= 750 && enemies.at(a)->shoot())
        {
            bullets.push_back(new Bullet(*sp, 0, 1, 4, enemies.at(a)->getCollision()->getPosition()));
        }
        if(enemies.at(a)->getCollision()->getPosition().x <= 10)
        {
            delete enemies.at(a);
            enemies.erase(enemies.begin()+a);
        }
    }
    //make shoot (heli)
}

void Map1::controlBridges()
{
    sf::Time time = cbridges.getElapsedTime();
    for(int a = 0; a < bridges.size(); a++)
    {
        bridges.at(a)->move({-0.2f * time.asMilliseconds(),0.f});
        cbridges.restart();
    }
    if(houseEnd)
    {
        house->move({-0.2f * time.asMilliseconds(),0.f});
    }
}

void Map1::update(int fuel, std::vector<sf::Sprite*> m)
{
    controlIA();
    controlBridges();
    if(bridges.front()->getPosition().x + bridges.front()->getGlobalBounds().width <= 10 && fuel >= 1000)
    {
        newBridge(false);
    }
    else if(!houseEnd && fuel < 1000)
    {
        newBridge(true);
        std::cout << bridges.size() << std::endl;
    }

    for(int a = 0; a < enemies.size(); a++)
    {
        enemies.at(a)->controlEnemy(m);
    }
    for(int a = 0; a < bullets.size(); a++)
    {
        bullets.at(a)->update();
    }
}

void Map1::draw(sf::RenderWindow& w)
{
    for(int a = 0; a < bridges.size(); a++)
    {
        w.draw(*bridges.at(a));
    }
    for(int a = 0; a < enemies.size(); a++)
    {
        enemies.at(a)->draw(w);
    }
    for(int a = 0; a < bullets.size(); a++)
    {
        bullets.at(a)->draw(w);
    }

    if(houseEnd)
    {
        w.draw(*house);
    }
}

std::vector<sf::Sprite*> Map1::getBridges()
{
    return bridges;
}

std::vector<Enemy*> Map1::getEnemies()
{
    return enemies;
}

std::vector<Bullet*> Map1::getBullets()
{
    return bullets;
}

bool Map1::getHouse(sf::RectangleShape* p)
{
    bool res = false;
    if(p->getPosition().x + p->getGlobalBounds().width/2 >= house->getPosition().x)
    {
        res = true;
    }
    return res;
}
