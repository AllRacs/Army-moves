#ifndef MAP2_H
#define MAP2_H

#include <Map.h>


class Map2 : public Map
{
    public:
        Map2(sf::Texture&);
        virtual ~Map2();
        void update(int);
        void draw(sf::RenderWindow&);
        void controlIA(int);
        void destroyBullet(int);
        void destroyEnemy(int);

        std::vector<sf::Sprite*> getFloor();
        std::vector<Enemy*> getEnemies();
        std::vector<Bullet*> getBullets();

        void playerShoot(int,sf::Vector2f);
        void hitEnemies();
        void destroyPBullet(int);

        void showCollisions();
        bool isFinal();

    protected:

    private:
        std::vector<sf::Sprite*> floor;
        sf::IntRect ss_Floor;
        sf::Texture *sp;
        sf::Sprite *heliport;
        sf::Clock cFloor, spawnAntiair, spawnJet, cspawnBullets, cEnd;
        bool fin, signalFinal, showHeliport, seeCollisions;

        std::vector<Enemy*> enemies;
        std::vector<Bullet*> bullets;
        std::vector<Bullet*> pBullets;

        void newFloor();
        void controlFloor(int);
        void newEnemyAC();
        void newEnemyJet();
        void managebullets();
};

#endif // MAP2_H
