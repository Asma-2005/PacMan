#pragma once
#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Menu
{
public:
	Text mainmenu[4];  //"Play" and "Instructions" and "Designers" and "Exit"
	Menu(float width, float height);  // Menu.cpp   width~and~height
	void draw(RenderWindow& window);  // display array mainmenu[4]
	void MoveUp();                    // Function Up
	void MoveDown();                 // Function Down
	void setselected(int n);
	int pressed() {
		return selected;
	}
	void checkMouseHover(RenderWindow& window);
	int getHoveredIndex(RenderWindow& window);
	Sprite drowscore;
	Texture DrowScore;

	~Menu();

private:
	int selected; //selected = Standing on option in array
	int selected1;
	Font font;

};
