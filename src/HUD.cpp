#include "HUD.h"

HUD::HUD(sf::Texture& spritesheet, int p)
{
    //ctor

    phase = p;
    scale = {1.006f, 1.534f};
    godMode = false;

    layout.setTexture(spritesheet);
    layout.setTextureRect(sf::IntRect(1430,862,1010,666));
    layout.setScale(scale.x, scale.y);
    layout.setPosition(0.f, 0.f);

    iconplayer = new sf::Sprite(spritesheet);
    iconplayer->setPosition({155.f,765.f});
    iconplayer->setScale(scale.x, scale.y);

    if(p==1)
    {
        iconplayer->setTextureRect(sf::IntRect(58,45,146,100));
    }
    else if(p==2)
    {
        iconplayer->setTextureRect(sf::IntRect(1330,83,150,90));
    }


    pixelFont = new sf::Font;
    if(!pixelFont->loadFromFile("fonts/VCR.ttf"))
    {
        std::cout << "Font not found" << std::endl;
    }

    ipoints = 0;
    ifuel = 0;
    ilives = 0;

    toogleInfo = false;
    info = new sf::Text;
    info->setFont(*pixelFont);
    info->setPosition(30.f, 45.f);
    info->setString("F4: SHOW INFO (TOGGLE) -- GODMODE (G): OFF");
    info->setCharacterSize(17);

    controls = new sf::Text;
    controls->setFont(*pixelFont);
    controls->setPosition(30.f, 65.f);
    controls->setString("CONTROLS-> Q/W: SHOOT - ARROWS L/R: MOVE - ARROW UP (CAR): JUMP - ARROW U/P (HELI): MOVE");
    controls->setCharacterSize(17);

    points = new sf::Text;
    points->setFont(*pixelFont);
    points->setPosition(450.f, 860.f);
    points->setString("POINTS");
    points->setCharacterSize(36);

    fuel = new sf::Text;
    fuel->setFont(*pixelFont);
    fuel->setPosition(800.f, 860.f);
    fuel->setString("FUEL");
    fuel->setCharacterSize(36);

    lives = new sf::Text;
    lives->setFont(*pixelFont);
    lives->setPosition(62.f, 810.f);
    lives->setString("LIVES");
    lives->setCharacterSize(36);

    phase1start = new sf::Text;
    phase1start->setFont(*pixelFont);
    phase1start->setPosition(390.f, 300.f);
    phase1start->setString("PHASE 1");
    phase1start->setCharacterSize(40);

    phase2start = new sf::Text;
    phase2start->setFont(*pixelFont);
    phase2start->setPosition(390.f, 300.f);
    phase2start->setString("PHASE 2");
    phase2start->setCharacterSize(40);

    phase2end = new sf::Text;
    phase2end->setFont(*pixelFont);
    phase2end->setPosition(300.f, 300.f);
    phase2end->setString("GAME OVER");
    phase2end->setCharacterSize(70);

    phase2end2 = new sf::Text;
    phase2end2->setFont(*pixelFont);
    phase2end2->setPosition(250.f, 400.f);
    phase2end2->setString("Teleporting you to phase 1");
    phase2end2->setCharacterSize(30);

    pointCount = 0;
    endPoint = new sf::Text;
    endPoint->setFont(*pixelFont);
    endPoint->setPosition(715.f + 10 * pointCount, 400.f);
    endPoint->setString(".");
    endPoint->setCharacterSize(30);

    std::cout << "HUD created" << std::endl;
}

HUD::~HUD()
{
    //dtor
    delete iconplayer;
    delete pixelFont;
    delete points;
    delete info;
    delete controls;
    delete fuel;
    delete lives;
    delete phase1start;
    delete phase2start;
    delete phase2end;
    delete phase2end2;
    delete endPoint;
}

void HUD::update(int f, int p, int l)
{
    updateFuel(f);
    updatePoints(p);
    updateLives(l);
    updateEndPoint();
}

void HUD::updatePoints(int p)
{
    ipoints = p;
    points->setString(std::to_string(ipoints));
}

void HUD::updateFuel(int f)
{
    ifuel = f;
    fuel->setString(std::to_string(ifuel));
}

void HUD::updateLives(int l)
{
    ilives = l;
    lives->setString(std::to_string(ilives));
}

void HUD::draw(sf::RenderWindow& w)
{
    w.draw(layout);
    w.draw(*info);
    if(toogleInfo)
        w.draw(*controls);

    w.draw(*points);
    w.draw(*fuel);
    w.draw(*lives);
    w.draw(*iconplayer);
    if(phase == 1 && ifuel >= 4800)
    {
        w.draw(*phase1start);
    }
    else if(phase == 2 && ifuel >= 4800)
    {
        w.draw(*phase2start);
    }
    if(phase == 2 && ifuel == 300)
    {
        w.draw(*phase2end);
        w.draw(*phase2end2);
        w.draw(*endPoint);
    }
}

int HUD::getPoints()
{
    return ipoints;
}

int HUD::getFuel()
{
    return ifuel;
}

void HUD::updateEndPoint()
{
    if(ifuel > 300)
    {
        cEndPoint.restart();
    }
    else if(ifuel == 300 && cEndPoint.getElapsedTime().asSeconds() >= 0.33)
    {
        if(pointCount++ < 3)
        {
            endPoint->setPosition(715.f + 10 * pointCount, 400.f);
        }
        else
        {
            pointCount = 0;
        }
        cEndPoint.restart();
    }
}

void HUD::showInfo()
{
    toogleInfo = !toogleInfo;
    if(!toogleInfo)
    {
        if(!godMode)
            info->setString("F4: SHOW INFO (TOGGLE)");
        else
            info->setString("F4: SHOW INFO (TOGGLE) -- GODMODE: ON");
    }
    else
    {
        changeGodMode(godMode);
    }
}

void HUD::changeGodMode(bool god)
{
    godMode = god;
    if(toogleInfo)
    {
        if(god)
        {
            info->setString("GODMODE (G): ON - F1: RESTART PHASE 1 - F2: RESTART PHASE 2 - F3: SHOW COLLIDERS");
        }
        else
        {
            info->setString("GODMODE (G): OFF - F1: RESTART PHASE 1 - F2: RESTART PHASE 2 - F3: SHOW COLLIDERS");
        }
    }
    else
    {
        if(!godMode)
            info->setString("F4: SHOW INFO (TOGGLE) -- GODMODE (G): OFF");
        else
            info->setString("F4: SHOW INFO (TOGGLE) -- GODMODE (G): ON");
    }
}
