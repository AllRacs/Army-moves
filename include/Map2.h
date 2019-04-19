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

    protected:

    private:
};

#endif // MAP2_H
