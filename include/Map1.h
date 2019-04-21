#ifndef MAP1_H
#define MAP1_H

#include <Map.h>


class Map1 : public Map
{
    public:
        Map1(sf::Texture&);
        virtual ~Map1();
        void update(int);
        void draw(sf::RenderWindow&);
        void controlIA();
        void controlBridges();
        void newBridge(bool);
        void newEnemy();

        std::vector<sf::Sprite*> getBridges();
        std::vector<Enemy*> getEnemies();
        std::vector<Bullet*> getBullets();

    protected:

    private:
        std::vector<sf::Sprite*> bridges;
        sf::IntRect ss_bridges[4];
        sf::Clock cbridges;

        sf::Sprite *house;

        sf::Texture *sp;

        bool houseEnd;

        std::vector<Enemy*> enemies;
        std::vector<Bullet*> bullets;
};

#endif // MAP1_H
