#ifndef MAP1_H
#define MAP1_H

#include <Map.h>


class Map1 : public Map
{
    public:
        Map1(sf::Texture&);
        virtual ~Map1();
        void update(int,std::vector<sf::Sprite*>);
        void draw(sf::RenderWindow&);
        void controlIA();
        void controlBridges();
        void newBridge(bool);
        void newEnemy(int);
        void destroyEnemy(int);
        void destroyBullet(int);

        void playerShoot(int,sf::Vector2f);
        void hitEnemies();
        void destroyPBullet(int);

        std::vector<sf::Sprite*> getBridges();
        std::vector<Enemy*> getEnemies();
        std::vector<Bullet*> getBullets();
        bool getHouse(sf::RectangleShape*);

        void showCollisions();

    protected:

    private:
        std::vector<sf::Sprite*> bridges;
        sf::IntRect ss_bridges[4];
        sf::Clock cbridges, cHeliSpawn;

        sf::Sprite *house;
        sf::Texture *sp;

        bool houseEnd, seeCollisions;

        std::vector<Enemy*> enemies;
        std::vector<Bullet*> bullets;
        std::vector<Bullet*> pBullets;
};

#endif // MAP1_H
