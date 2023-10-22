#ifndef TEAM_HPP
#define TEAM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

#include "../include/player.hpp"


class Team{
    protected:
        std::string name;
        int score = 0;
        std::vector <Player*> players;
        //////////////////////////////////
        std::vector<int> scores;
        std::vector<int> GFs;
        std::vector<int> GAs;


    
    public:
        Team(std::string _name);
        Team(std::string _name, std::vector<std::string> goalKeepers,
                                std::vector<std::string> defenders,
                                std::vector<std::string> midFielders,
                                std::vector<std::string> forwards);
        std::string getName();
        void printPlayers(int week, std::string filter = "all", bool ranked = false);
        std::vector<int> getScores();
        std::vector<int> getGFs();
        std::vector<int> getGAs();
        void addScore(int _score);
        void addGF(int _GF);
        void addGA(int _GA);
        Player* getPlayer(std::string playerName);
        int calcScoreTillWeek(int week);
        int calcGoalForTillWeek(int week);
        int calcGoalAgainstTillWeek(int week);

        static bool sortByScore(Player* a, Player* b, int currentWeek);
        static bool sortByName(Player* a, Player* b);

        std::vector<Player*> getPlayers();



};

class FantasyTeam : public Team{
    public:
        FantasyTeam(std::string name);
        void addPlayer(Player* player);
        void removePlayer(Player* player);
};

#endif