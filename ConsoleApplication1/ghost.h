#pragma once
#include "Graph.h"
#include <SFML/Graphics.hpp>
#include"pacman.h"

using namespace sf;

class ghost
{
public:
    ghost();

    void movement(pacman& pac ,Graph& g);
    void draw(RenderWindow& window);
    bool checkCollision(pacman& pac);
    int i, j;
    Sprite ghostSprite;
    int moveCounter;
    vector<int> path;
	bool isVisible=1;
public:
    int status;
    Texture ghostTex;
    int frame;
    float speed;
    Graph g;
     

};