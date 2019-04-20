#ifndef MAP2_H
#define MAP2_H

#include <Map.h>


class Map2 : public Map
{
    public:
        Map2(sf::Texture&);
        virtual ~Map2();
        void update();
        void draw(sf::RenderWindow&);
        void controlIA();

        std::vector<sf::Sprite*> getFloor();
        std::vector<Enemy*> getEnemies();
        std::vector<Bullet*> getBullets();

    protected:

    private:
        std::vector<sf::Sprite*> floor;
        sf::IntRect ss_Floor;

        std::vector<Enemy*> enemies;
        std::vector<Bullet*> bullets;
};

#endif // MAP2_H
