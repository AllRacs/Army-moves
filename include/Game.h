#ifndef GAME_H
#define GAME_H


class Game
{
    public:
        Game(int w, int h, std::string str);


    protected:

    private:

        sf::RenderWindow *wind;
        int fps;
        sf::Texture *player;
        sf::Sprite *player_s;
        sf::Clock clock;

        float scene_vel;
        int fuel, distance;

        void loop();
        void control(sf::Clock c);
        void jump();
};

#endif // GAME_H
