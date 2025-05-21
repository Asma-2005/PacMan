#pragma once
#include "Graph.h"
#include <SFML/Graphics.hpp>
#include"pacman.h"

using namespace sf;

class ghost
{
public:
    ghost(int x,int y,string photo);
    void setVulnerable();
    void movement(pacman& pac, Graph& g,int id);
    void draw(RenderWindow& window);
    bool checkCollision(pacman& pac);
    bool isVulnerable();
    bool isDying = 0;
    int i, j;
    Sprite ghostSprite;
    int moveCounter;
    vector<int> path;
    bool isVisible = 1;
    bool isFrozen;
    int homeId = 11* Graph::COLS + 19;
    Clock freezeClock;

public:
    int status;
    Texture ghostWeakShape;
    Texture ghostTex, ghostEyes;
    int frame;
    float speed;
    Graph g;
    int counttime;

    bool vulnerable;
    float vulnerableDuration = 6.0f;
    Clock vulnerableClock;

    int countRemainingFood(const vector<unique_ptr<Food>>& foodList);
    bool isStuck() const;
    int lastVisitedNode;
    int stationaryCounter;

};

  