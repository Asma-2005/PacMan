#pragma once
#include "Graph.h"
#include <SFML/Graphics.hpp>
#include"pacman.h"

using namespace sf;

class ghost
{
public:
    ghost(int x,int y);
    void setVulnerable();
    void movement(pacman& pac, Graph& g);
    void draw(RenderWindow& window);
    bool checkCollision(pacman& pac);
    bool isVulnerable();
    bool isDying = 0;
    int i, j;
    Sprite ghostSprite;
    int moveCounter;
    vector<int> path;
    bool isVisible = 1;
    bool isFrozen = 0;
    int homeId = 18 * Graph::COLS + 11;
    Clock freezeClock;
    bool freezeStarts = 0;

public:
    int status;
    Texture ghostWeakShape;
    Texture ghostTex;
    int frame;
    float speed;
    Graph g;

    bool vulnerable;
    float vulnerableDuration = 6.0f;
    Clock vulnerableClock;

};

  