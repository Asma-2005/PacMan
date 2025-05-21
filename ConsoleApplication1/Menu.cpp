#include "Menu.h"
#include<SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>


using namespace std;
using namespace sf;

Menu::Menu(float width, float height)
{
	font.loadFromFile("Assets/font/Prison Tattoo.ttf");

	mainmenu[0].setFont(font);
	mainmenu[0].setFillColor(Color::Green);
	mainmenu[0].setString("Play");
	mainmenu[0].setCharacterSize(110);
	mainmenu[0].setPosition(Vector2f(width / 4, height / (2)));


	mainmenu[1].setFont(font);
	mainmenu[1].setFillColor(Color::White);
	mainmenu[1].setString("Instructions");
	mainmenu[1].setCharacterSize(110);
	mainmenu[1].setPosition(Vector2f(width / 4, height / (2) + 110));

	mainmenu[2].setFont(font);
	mainmenu[2].setFillColor(Color::White);
	mainmenu[2].setString("Designers");
	mainmenu[2].setCharacterSize(110);
	mainmenu[2].setPosition(Vector2f(width / 4, height / (2) + 220));

	mainmenu[3].setFont(font);
	mainmenu[3].setFillColor(Color::White);
	mainmenu[3].setString("Exit");
	mainmenu[3].setCharacterSize(110);
	mainmenu[3].setPosition(Vector2f(width / 4, height / (2) + 330));

	selected = 0;
	selected1 = 0;

	DrowScore.loadFromFile("Assets/images/score.png");
	
	drowscore.setPosition(1700, 100);
	drowscore.setTexture(DrowScore);
	drowscore.setScale(0.1, 0.1);

}


Menu::~Menu() {}


void Menu::setselected(int n) {
	selected = n;
}

void Menu::draw(RenderWindow& window) {
	for (int i = 0; i < 4; i++)
	{
		window.draw(mainmenu[i]);
	}
	window.draw(drowscore);
}

void Menu::MoveDown() {
	selected = selected1;
	if (selected + 1 <= 4) //not exit
	{
		mainmenu[selected].setFillColor(Color::White);
		selected++;
		if (selected == 4)
		{
			selected = 0;
		}
		mainmenu[selected].setFillColor(Color::Green);
	}
	selected1 = selected;

}

void Menu::MoveUp()
{
	selected = selected1;
	if (selected - 1 >= -1)  //not play
	{
		mainmenu[selected].setFillColor(Color::White);
		selected--;
		if (selected == -1)
		{
			selected = 3;
		}
		mainmenu[selected].setFillColor(Color::Green);
	}
	selected1 = selected;

}

void Menu::checkMouseHover(RenderWindow& window)     //Move the mouse to change the color.
{
	
	for (int i = 0; i < 4; i++)
	{
		selected = selected1;
		if (mainmenu[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
		{
			mainmenu[selected].setFillColor(Color::White);  // Before the mouse moves
			selected = i;                                                              // Convert to new
			mainmenu[selected].setFillColor(Color::Green);  //After the mouse moves
		}
		selected1 = selected;
	}
	if (drowscore.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
	{
		drowscore.setScale(0.15f, 0.15f);
		selected = 4;
	}
	else
	{
		drowscore.setScale(0.1f, 0.1f); 
	}
		
}
int Menu::getHoveredIndex(RenderWindow& window)
{
	for (int i = 0; i < 4; i++)
	{
		if (mainmenu[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
		{
			return i;
		}
	}
	if (drowscore.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
	{
		return 4;
	}
	return -1;
}
