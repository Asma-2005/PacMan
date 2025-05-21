#pragma once
#include <SFML/Graphics.hpp>
#include "Graph.h"
#include "Food.h"

using namespace std;
using namespace sf;
class TileRenderer {
public:
    TileRenderer( int tileSize,int level);
    void draw(RenderWindow& window);
    void checklevel(int value);
    vector<unique_ptr<Food>>& getfoodList();
    void initializeFood();


private:
    int tileSize;
    Texture texture0, texture1;
    Sprite sprite0, sprite1;
    vector<unique_ptr<Food>> foodList; 
};
