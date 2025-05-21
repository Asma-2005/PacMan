#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<sstream>
#include<stdlib.h>
#include<stdio.h>
#include<ctime>
#include<time.h>
#include<string>
#include<random>
#include<iomanip>
#include<vector>
#include<fstream>
#include<Windows.h>
#include"Menu.h"
#include<math.h>
#include<SFML/Window/Event.hpp>

//Music menu;  sound[0]
//Music intro;  sound[1]
//Music eat;   sound[2]
//Music eat fruit; sound[3]
//music scatter ghost  sound[4]
//Music siren;  sound[5]
//Music winnLife;   sound[6]
//Music Death;   sound[7]
//music winner; sound[8]
class SoundManager
{

public:

    Music sound[9];

    bool initialize() {
        if (!sound[0].openFromFile("Assets/Sounds/menu.wav")) {
            cout << "ERROR: Can't load sound menu.wav\n";
            return false;
        }

        if (!sound[1].openFromFile("Assets/Sounds/intro.wav"))
        {
            cout << "ERROR: Can't load sound intro.wav\n";
            return false;
        }

        if (!sound[2].openFromFile("Assets/Sounds/eat.wav")) {
            cout << "ERROR: Can't load sount eat.wav\n";
            return false;
        }

        if (!sound[3].openFromFile("Assets/Sounds/eatFruit.wav")) {
            cout << "ERROR: Can't load  sound winLife.wav\n";
            return false;
        }

        if (!sound[4].openFromFile("Assets/Sounds/scatter ghost.wav")) {
            cout << "ERROR: Can't load sound Death.wav\n";
            return false;
        }

        if (!sound[5].openFromFile("Assets/Sounds/siren.wav")) {
            cout << "ERROR: Can't load sound eatFruit.wav\n";
            return false;
        }
        if (!sound[6].openFromFile("Assets/Sounds/PacDeath.wav"))
        {
            cout << "ERROR: Can't load sound PacDeath.wav\n";
            return false;
        }

        /*
        if (!sound[7].openFromFile("Assets/Sounds/winner.wav")) {
            cout << "ERROR: Can't load sound winner.wav\n";
            return false;
        }
        if (!sound[8].openFromFile("Assets/Sounds/GhostDeath.wav")) {
            cout << "ERROR: Can't load sound GhostDeath.wav\n";
            return false;
        }
        */
        return true;
    }

};