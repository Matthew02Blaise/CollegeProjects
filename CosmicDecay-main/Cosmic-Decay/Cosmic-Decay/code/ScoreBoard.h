#pragma once
#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "httplib.h"
#include <sstream>
#include <fstream>

using namespace sf;
using namespace std;

class ScoreBoard {
private:
    const std::string DREAMLO_PRIVATE_KEY = "1yAU-9fw8EaEC5sXzaXtNwzSujXujP1E-5P4G8I6wnrA";
    const std::string DREAMLO_PUBLIC_KEY = "67befb9a8f40be0240660a9e";

public:
    void submitScore(const std::string& playerName, int score);
    std::string getLeaderboardText();  // Changed to return string
    std::string captureInitials(RenderWindow& window, const Font& font); // capture 3 initials
};

#endif
