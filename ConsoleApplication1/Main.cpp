#include <iostream>
#include<stack>
#include<queue>
#include<deque>
#include<vector>
#include<set>
#include "Graph.h"
#include<map>
#include<unordered_map>
#include<unordered_set>
#include<sstream>
#include<stdlib.h>
#include<stdio.h>
#include<ctime>
#include<time.h>
#include<string>
#include<random>
#include<iomanip>
#include<fstream>
#include<math.h>
#include <iomanip>
#include<SFML/Window/Event.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include"Menu.h"
#include"SoundManager.h"
#include"ghost.h";
#include "pacman.h"
#include<dsound.h>
#include "TileRenderer.h"
#include "FileHandler.h"

using namespace std;
using namespace sf;


/*
**************************************************************
*      page number        *       fun                        *
**************************************************************
*       1000              *         mainmenu                 *
*        -1               *         close=Exit               *
*         0               *         Game_Play                *
*         1               *         instruction              *
*         2               *         Designers                *
*         3               *         Score                    *
**************************************************************
*      1000               *         exit game                *
*         7               *         restart game             *
*         8               *         next  level              * 
**************************************************************
* 
*/

int Design(RenderWindow& window);
int instruction(RenderWindow& window);
int Game_Play(RenderWindow& window, int level,string &name, SoundManager& soundManagerr);
void drawMenu(RenderWindow& window, Menu& menu, Sprite& bg);
void handleEvents(RenderWindow& window, Menu& menu, int& pagenum);
void numphoto_checkMouseHover(RenderWindow& window, RectangleShape numplay[], int& selectedOption);
void select_checkMouseHover(RenderWindow& window, Sprite difficulty[], int numphoto, int& selectedOption);
int SelectDifficulty(RenderWindow& window,string &name);
int score_player(RenderWindow& window);
int showGameOverScreen(RenderWindow& window);
int meungameplay(RenderWindow& window, bool winner, int level, string name, int score);


stack<Score> s;
FileHandler score_file;


int main() {
    RenderWindow window(VideoMode(1920, 1080), "Game", Style::Fullscreen);
    SoundManager soundManagerr;
    if (!soundManagerr.initialize()) {
        cout << "ERROR: Can't load sounds\n";
        system("pause");
        return -1;
    }
    soundManagerr.sound[0].setLoop(true);
    soundManagerr.sound[0].play();

    int pagenum = 1000; // Index for choosing
    Menu menu(1920, 1080);
    Texture mainmenubg;
    if (!mainmenubg.loadFromFile("Assets/images/menu main.png")) {
        cout << "ERROR: Can't load menu main.jpg\n";
        window.close();
        return -1;
    }
    Sprite bg;
    bg.setPosition(0, -200);
    bg.setTexture(mainmenubg);

    string name;
  
    
	//Read scores from the file
	
	score_file.jsonRead();
	s = score_file.jsonRead();
  
  

    while (true) {

        if (pagenum == 1000) {
            while (window.isOpen()) {
                handleEvents(window, menu, pagenum);
                if (pagenum != 1000) {
                    break;
                }

                drawMenu(window, menu, bg);
            }
            if (pagenum == 0) {
                int level = SelectDifficulty(window,name);
                do
                {
                    for (int i = 0; i < 9; i++)
                        soundManagerr.sound[i].stop();

                  soundManagerr.sound[1].play();
                  pagenum = Game_Play(window, level, name, soundManagerr);
                  if (pagenum == 8) level++;
                } while (pagenum != 1000);
                soundManagerr.sound[0].play();
            }
            if (pagenum == -1) {
                soundManagerr.sound[0].stop();
                window.close();
                break;
            }
            if (pagenum == 2) {
                pagenum = Design(window);
            }
            if (pagenum == 1) {
                pagenum = instruction(window);
            }
            if (pagenum == 3) {
                pagenum = score_player(window);
            }


            for (int i = 1; i < 9; i++)
            {
                soundManagerr.sound[i].stop();
            }
        }
    }
    return 0;
}

void handleEvents(RenderWindow& window, Menu& menu, int& pagenum) {
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			break;
		}
		if (event.type == Event::KeyPressed) {
			if (event.key.code == Keyboard::Up) {
				menu.MoveUp();
			}
			if (event.key.code == Keyboard::Down) {
				menu.MoveDown();
			}
			if (event.key.code == Keyboard::Return) {
				if (menu.pressed() == 0) {
					pagenum = 0;
				}
				if (menu.pressed() == 1) {

					pagenum = 1;
				}
				if (menu.pressed() == 2) {

					pagenum = 2;
				}
				if (menu.pressed() == 3) {
					pagenum = -1;
				}
                
			}
		}

		if (event.type == Event::MouseMoved) {
			menu.checkMouseHover(window);
		}

		if (event.type == Event::MouseButtonPressed) {
			if (event.mouseButton.button == Mouse::Left)
			{
				int selectedItemIndex = menu.getHoveredIndex(window);
				if (selectedItemIndex != -1 && selectedItemIndex == menu.pressed()) {
					if (menu.pressed() == 0) {
						pagenum = 0;
					}
					if (menu.pressed() == 1) {

						pagenum = 1;
					}
					if (menu.pressed() == 2) {

						pagenum = 2;
					}
					if (menu.pressed() == 3) {
						pagenum = -1;
					}
                    if (menu.pressed() == 4) {
                        pagenum = 3;
                    }
				}
			}
		}
	}
}

void drawMenu(RenderWindow& window, Menu& menu, Sprite& bg)
{
	window.clear();
	window.draw(bg);
	menu.draw(window);
	window.display();
}

void numphoto_checkMouseHover(RenderWindow& window, RectangleShape numplay[], int& selectedOption)
{
	bool check = 0;
	for (int i = 0; i < 6; i++)
	{
		if (numplay[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
		{
			selectedOption = i;
			check = 1;
		}
	}
	if (check == 0)
	{
		selectedOption = -1;
	}

}

int Design(RenderWindow& window)
{
	Texture background;
	background.loadFromFile("Assets/images/Designers.jpg");
	Sprite bg;
	bg.setTexture(background);
	Font font;
	font.loadFromFile("Assets/font/Prison Tattoo.ttf");
	Text t[8];
	for (int i = 0; i < 8; i++)
	{
		t[i].setFont(font);
		t[i].setCharacterSize(70);
		t[i].setFillColor(Color::White);
		t[i].setPosition(520, (920));
	}
	t[0].setString("Taha Mustafa Abdel Fattah");
	t[1].setString("\t  Reham Maher Roshdy");
	t[2].setString("  Yousab Ashraf Makram");
	t[3].setString("Mohamed Sameh El-Sayed");
	t[4].setString("Asmaa Walid Sayed Moawad");
	t[5].setString("\tYoussef Khaled Hussein");
	t[6].setString("\tRana Mohamad Fattouh ");
	t[7].setString("It was developed by them");


	RectangleShape Photo[6];

	Photo[0].setPosition(70, 210.f);
	Photo[1].setPosition(380.f, 210.f);
	Photo[2].setPosition(690.f, 210.f);
	Photo[3].setPosition(1000.f, 210.f);
	Photo[4].setPosition(1310, 210.f);
	Photo[5].setPosition(1630.f, 210.f);
	for (int i = 0; i < 6; i++)
	{
		Photo[i].setSize(Vector2f(230, 660));
		Photo[i].setFillColor(Color::Green);
	}


	int numphoto = -1;
	int selectedOption = -1;
	int checkphoto = -1;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed())
			{
				window.close();
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				return 1000;
			}
		}
		if (event.type == Event::MouseMoved)
		{
			numphoto_checkMouseHover(window, Photo, selectedOption);
		}
		if (event.type == Event::MouseMoved)
		{
			for (int i = 0; i < 6; i++)
			{
				if (Photo[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
				{
					checkphoto = i;
					break;
				}
			}
		}
		if (checkphoto == selectedOption)
		{
			numphoto = checkphoto;
		}
		else
		{
			numphoto = -1;
		}


		window.clear();
		window.draw(bg);
		if (numphoto == -1)
		{
			window.draw(t[7]);
		}
		else
		{
			window.draw(t[numphoto]);
		}

		window.display();
	}
}

int instruction(RenderWindow& window)
{
	Texture background;
	Sprite bg;
	background.loadFromFile("Assets/images/instructions.jpg");

	Sprite KEY;
	Texture key;
	key.loadFromFile("Assets/images/key.png");


	KEY.setPosition(1200, 650);
	KEY.setScale(0.6, 0.6);

	KEY.setTexture(key);
	bg.setTexture(background);

	Sprite Gameimage;
	Texture gameimage;
	gameimage.loadFromFile("Assets/images/Gameimage.png");
	Gameimage.setPosition(900, 100);
	Gameimage.setScale(1.7, 1.7);
	Gameimage.setTexture(gameimage);



	Font font;
	font.loadFromFile("Assets/font/Prison Tattoo.ttf");
	Text t[5];
	for (int i = 0; i < 5; i++)
	{
		t[i].setFont(font);
		t[i].setCharacterSize(150);
		t[i].setFillColor(Color::White);
	}
	t[0].setPosition(200, 200);
	t[1].setPosition(250, 400);
	t[2].setPosition(200, 600);
	t[3].setPosition(1110, 900);
	t[4].setPosition(900, 400);


	t[3].setCharacterSize(60);
	t[4].setCharacterSize(45);



	t[0].setString("HOW");
	t[1].setString("TO");
	t[2].setString("PLAY");
	t[3].setString("Control Buttons");
	t[4].setString("Move Pac-Man using the arrow keys and \n"
		"eat all the dots in the maze. Avoid the \n"
		"ghosts,but if you eat a big dot, the \n"
		"ghosts turn blue and you can eat them. \n"
		"Clear all the dots to go tothe next level.");




	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed())
			{
				window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				return 1000;   //Return to menu
			}


		}

		window.clear();
		window.draw(bg);
		window.draw(KEY);
		window.draw(Gameimage);

		for (int i = 0; i < 5; i++)
		{
			window.draw(t[i]);
		}
		window.display();
	}
}

void select_checkMouseHover(RenderWindow& window, Sprite difficulty[], int numphoto, int& selectedOption) {
	bool check = 0;
	for (int i = 0; i < 3; i++)
	{
		if (difficulty[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
		{
			selectedOption = i;
			check = 1;
		}
	}
	if (check == 0)
	{
		selectedOption = -1;
	}
}

int SelectDifficulty(RenderWindow& window, string & name) {
    int selectedOption = -1;
    Texture background;
    Sprite bg;
    background.loadFromFile("Assets/images/select difficulty.png");
    bg.setTexture(background);
    bg.setScale(1.9, 1);
    bg.setPosition(0, 0);

    Texture difficulty[3];
    Sprite df[3];
    difficulty[0].loadFromFile("Assets/images/select easy.png");
    difficulty[1].loadFromFile("Assets/images/select medium.png");
    difficulty[2].loadFromFile("Assets/images/select hard.png");

    bool enter = true;

    Font font;
    font.loadFromFile("Assets/font/Prison Tattoo.ttf");
    Text t[2];
    for (int i = 0; i < 2; i++)
    {
        t[i].setFont(font);
        t[i].setCharacterSize(70);
        t[i].setFillColor(Color::White);
        t[i].setPosition(500+i*450, 400);
    }
    t[0].setString("Name Player ");

    Clock clock;
    bool showCursor = true;
    Time blinkTime = seconds(0.5f);

    Text cursor;
    cursor.setFont(font);
    cursor.setString("|");
    cursor.setCharacterSize(70);
    cursor.setFillColor(Color::White);

    for (int i = 0; i < 3; i++)
    {
        df[i].setTexture(difficulty[i]);
    }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::MouseMoved&&!enter)
            {
                select_checkMouseHover(window, df, 3, selectedOption);
            }

            if (event.type == Event::MouseButtonPressed&&!enter) {
                if (event.mouseButton.button == Mouse::Left)
                {
                    if (selectedOption != -1)
                    {
                        return selectedOption;

                    }
                }
            }

            if (event.type == Event::TextEntered)
            {

                if (enter)
                {
                    if (name.size() < 10)
                    {
                        name += static_cast<char>(event.text.unicode);
                    }
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::BackSpace))
            {
                if (enter && name.size() > 0)
                {
                    name.resize(name.size() - 1);
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter) && name.size() > 1)
            {
                enter = false;
            }
            
        }
        t[1].setString(name);

        window.clear();
        window.draw(bg);           
        window.draw(t[1]);
        window.draw(t[0]);

        if (enter && showCursor)
        {
            cursor.setPosition(t[1].getPosition().x + t[1].getGlobalBounds().width + 5, t[1].getPosition().y);
            window.draw(cursor);
        }
        if (clock.getElapsedTime() >= blinkTime)
        {
            showCursor = !showCursor;
            clock.restart();
        }

        for (int i = 0; i < 3; i++)
        {
            if (selectedOption == i)
            {
                df[i].setScale(1.2f, 1.2f);
                df[i].setPosition(400 * i + 400 - 20, 550 - 20);
                df[i].setColor(i == 0 ? Color::Green : (i == 1 ? Color::Yellow : Color::Red));
            }
            else
            {
                df[i].setScale(1.f, 1.f);
                df[i].setColor(Color::White);
                df[i].setPosition(400 * i + 400, 550);
            }

            window.draw(df[i]);
        }

        window.display();
    }
}


int Game_Play(RenderWindow& window, int level,string& name, SoundManager& soundManagerr) {

    bool DeathSoundBool = false;

    window.setFramerateLimit(60);
    bool checkstart = 1;
    Graph g;
    pacman player(19, 20);
    TileRenderer tileRenderer(48, level);
    //here we are setting the ghost to its home
    ghost myghost(18,11,0);
    ghost myghost1(17, 11,1);
    ghost myghost2(21, 11,2);
    ghost myghost3(22, 11,3);


    Clock clock;
    int numghost = 1;
    int countclock = 0;
    tileRenderer.initializeFood();

    // Score setup
    player.score.value = 0;
    player.score.userName = name;
    Font font;
    font.loadFromFile("Assets/font/Prison Tattoo.ttf");



    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(55);
    scoreText.setFillColor(Color::White);


    Text t;

    t.setFont(font);
    t.setCharacterSize(40);
    t.setFillColor(Color::White);
    t.setPosition(920-(name.size()*6), 0);
    t.setString(name);

    auto& foodList = tileRenderer.getfoodList();


    // Game loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
            if (Keyboard::isKeyPressed(Keyboard::Escape)) return 1000;
        }
        player.movement();
        myghost.movement(player, g,level);

        
        if (numghost >= 2)myghost1.movement(player, g,level); 
        if (numghost >= 3)myghost2.movement(player, g,level);  
        if (numghost >= 4)myghost3.movement(player, g,level);

        for (auto it = foodList.begin(); it != foodList.end(); ) {
            if (player.pacsprite.getGlobalBounds().intersects((*it)->getBounds())) {
                if ((*it)->getValueScore() == 1) {soundManagerr.sound[2].stop();soundManagerr.sound[2].play(); }
                if ((*it)->getValueScore() == 20) { soundManagerr.sound[3].stop(); soundManagerr.sound[3].play(); }
                if ((*it)->getValueScore() == 10)
                {
                    myghost.setVulnerable();
                    if (numghost >= 2)myghost1.setVulnerable();
                    if (numghost >= 3)myghost2.setVulnerable();
                    if (numghost >= 4)myghost3.setVulnerable();
                    soundManagerr.sound[4].stop();
                    soundManagerr.sound[4].setLoop(true);
                    soundManagerr.sound[4].play();
                    soundManagerr.sound[5].stop();
                }
                player.score.value += (*it)->getValueScore();
                it = foodList.erase(it);
            }
            else {
                ++it;
            }
        }
        if (clock.getElapsedTime().asSeconds() > 5.0f) {
            countclock++;clock.restart();
        }
        if (countclock > 3) {
            numghost++;countclock = 0;
        }

        // Update score text
        scoreText.setString(std::to_string(player.score.value));
        if (player.score.value < 10) scoreText.setPosition(950, 45);
        else if (player.score.value < 100) scoreText.setPosition(930, 45);
        else scoreText.setPosition(910, 45);

        // Render
        window.clear();
        tileRenderer.draw(window);
        player.draw(window);
        myghost.draw(window);
        myghost1.draw(window);
        myghost2.draw(window);
        myghost3.draw(window);
        window.draw(scoreText);
        window.draw(t);
        window.display();

        if (myghost.vulnerable && myghost.vulnerableClock.getElapsedTime().asSeconds() > myghost.vulnerableDuration) {
            soundManagerr.sound[4].stop();
            soundManagerr.sound[5].play();
        }

        if (checkstart) {

            Sleep(4300);
            soundManagerr.sound[5].setLoop(true);
            soundManagerr.sound[5].play();
            checkstart = 0;

        }

        if (player.isDying && !DeathSoundBool) {
            soundManagerr.sound[5].stop();
            soundManagerr.sound[6].play();
            DeathSoundBool = 1;
        }

        if (player.isDead) {
            soundManagerr.sound[6].stop();
            s.push(player.score);
            score_file.jsonWrite(s);
            cout << "Dead\n";
            return meungameplay(window, false, level, player.score.userName, player.score.value);
        }
        if (tileRenderer.getfoodList().empty()) {
            
            s.push(player.score);
            score_file.jsonWrite(s);
            cout << "winner\n";
            return meungameplay(window, true, level, player.score.userName, player.score.value);
        }

        
    }
}



int showGameOverScreen(RenderWindow& window) {
    Texture gameOverTexture;
    if (!gameOverTexture.loadFromFile("Assets/images/GameOver4.jpg")) {
        cout << "ERROR: Can't load game_over.png\n";
        return 1000;
    }
    Sprite gameOverSprite;
    gameOverSprite.setTexture(gameOverTexture);
    gameOverSprite.setPosition(0, 0);

    Clock timer;
    while (timer.getElapsedTime().asSeconds() < 3.0f) {
        window.draw(gameOverSprite);
        window.display();
    }
    return 1000;
}


int score_player(RenderWindow& window) {
    stack<Score> score = s;
    Texture background ;
    background.loadFromFile("Assets/images/bg_score.jpg");
    Sprite bg;
    bg.setTexture(background);
    bg.setPosition(870, 0);
    bg.setScale(1.3, 1.12);
    Font font;
    font.loadFromFile("Assets/font/Prison Tattoo.ttf");
    Text t[10];
    int i = 0;
    while (!score.empty()&&i<10) {
        t[i].setFont(font);
        t[i].setCharacterSize(40);
        t[i].setFillColor(Color::White);
        t[i].setPosition(50, 100+i*60);
        t[i].setString("Player name: " + score.top().userName + " with a score of " + to_string(score.top().value) );
        score.pop();
        i++;
    }
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed())
            {
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                return 1000;   
            }
        }
        window.clear();
        window.draw(bg);
        for (int j = 0; j < i ; j++)
        {
            window.draw(t[j]);
        }
        window.display();
    }
}


int meungameplay(RenderWindow& window,bool winner,int level ,string name,int score  ) {
    int select = -1;
    int numoption = 0;
    int selectedOption = -1;
    Texture background[2];
    background[0].loadFromFile("Assets/images/GameOver4.jpg");
    background[1].loadFromFile("Assets/images/GameOver4.jpg");
    Sprite bg;
    bg.setTexture(background[0]);
    bg.setScale(0.8, 0.8);
    bg.setPosition(200, -100);
    Texture Option[3];
    Option[0].loadFromFile("Assets/images/EXIT.PNG");
    Option[1].loadFromFile("Assets/images/NEXTLEVEL.png");
    Option[2].loadFromFile("Assets/images/RESTART.png");
    Sprite options[2];
    options[0].setTexture(Option[0]);


    Font font;
    font.loadFromFile("Assets/font/Prison Tattoo.ttf");
    Text t;
    t.setFont(font);
    t.setCharacterSize(60);
    t.setFillColor(Color::White);
    t.setPosition(250, 600);
 
    if (winner)
    {
        bg.setTexture(background[1]);
        options[1].setTexture(Option[1]);
        
        if (level==2) numoption = 1;
        else  numoption = 2;
        t.setString("The winner's name is " + name + " with a score of " + to_string(score));
    }
    else
    {
        numoption = 2;
        bg.setTexture(background[0]);
        options[1].setTexture(Option[2]);
        t.setString("The Loser's name is " + name + " with a score of " + to_string(score));
    }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed())
            {
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                return 1000;
            }

            if (event.type == Event::MouseMoved )
            { 
                select_checkMouseHover(window, options, numoption, selectedOption);
            }

            if (event.type == Event::MouseButtonPressed ) {
                if (event.mouseButton.button == Mouse::Left)
                {
                    if (selectedOption != -1)
                    {
                        select = selectedOption;

                    }
                }
            }
        }
        for (int i = 0; i < numoption; i++)
        {
            if (selectedOption == i)
            {
                options[i].setScale(1.4f, 1.4f);
                options[i].setPosition(450 * i + 550 - 20, 750 - 20);
            }
            else
            {
                options[i].setScale(1.2f, 1.2f);
                options[i].setPosition(450 * i + 550, 750);
            }
        }
        window.clear();
        window.draw(bg);
        window.draw(options[0]);

        if (numoption==2)
        {
         window.draw(options[1]);
        }
        window.draw(t);
        window.display();

        if (select==0)
        {
            return 1000;
        }
        else if (select==1)
        {
            if (winner)
            {
                return 8;
            }
            else
            {
                return 7;
            }

        }
    }
}

