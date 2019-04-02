#ifndef GAME_H
#define GAME_H
#include "Mapa.h"
#include "Jugador.h"


class Game
{
    public:
        Game(int w, int h, std::string str);


    protected:

    private:

        sf::RenderWindow *wind;
        int fps;
        Jugador *jugador;
        Mapa *mapa;
        sf::Clock clock;

        float scene_vel;
        int fuel, distance;

        void loop();

};

#endif // GAME_H
