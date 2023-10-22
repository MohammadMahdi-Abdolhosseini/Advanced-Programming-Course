#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "../include/team.hpp"
#include "../include/player.hpp"

class Game{
    private:
        std::vector <std::string> teams;
        std::vector <float> teamScores;
        std::vector <std::string> yellowCards;
        std::vector <std::string> redCards;
        std::vector <std::string> playersWithScroe;
        std::vector <float> playerScores;
    
    public:
        Game();

};

#endif