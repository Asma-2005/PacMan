#pragma once
#include <SFML/Graphics.hpp>
#include "Graph.h"
#include "Score.h"

using namespace sf;

class pacman {
public:
    pacman(int x,int y);

    void movement();
    void draw(RenderWindow& window);
    int i, j;
    Sprite pacsprite;
    int nextStatus;

    Score score;

public:
    int status;
    Texture pactexture;
    int frame;
    float speed;
    int restframe;
    Graph g;
};