#ifndef MAP1_H
#define MAP1_H

#include <Map.h>


class Map1 : public Map
{
    public:
        Map1(sf::Texture&);
        virtual ~Map1();
        void update();
        void draw(sf::RenderWindow&);
        void controlIA();
        void newBridge();
        std::vector<sf::Sprite*> getBridges();

    protected:

    private:
        std::vector<sf::Sprite*> bridges;
        sf::IntRect ss_bridges[4];
};

#endif // MAP1_H
