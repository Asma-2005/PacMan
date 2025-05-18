#pragma once
#include <SFML/Graphics.hpp>
#include "Graph.h"
#include "Score.h"

using namespace sf;

class pacman {
public:
    pacman(int x, int y);

    void movement();
    void draw(RenderWindow& window);
    Clock dyingClock;
    int i, j;
    Sprite pacsprite;
    int nextStatus;

    bool isDying;
    bool isDead;
    float frameDuration = 0.3f;
    Score score;


public:
    int count = 0;
    int f = 0;
    int status;
    Texture pactexture;
    Texture pacDeath;
    int frame;
    float speed;
    int restframe;
    Graph g;
};