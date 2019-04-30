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
        std::vector<sf::Sprite*> getFloor();
        std::vector<Enemy*> getEnemies();
        std::vector<Bullet*> getBullets();

        void showCollisions();

    protected:

    private:
        std::vector<sf::Sprite*> floor;
        sf::IntRect ss_Floor;
        sf::Texture *sp;
        sf::Sprite *heliport;
        sf::Clock cFloor, spawnAntiair, cspawnBullets;
        bool fin, showHeliport, seeCollisions;

        std::vector<Enemy*> enemies;
        std::vector<Bullet*> bullets;

        void newFloor();
        void controlFloor(int);
        void newEnemyAC();
        void manageACbullets();
};

#endif // MAP2_H
