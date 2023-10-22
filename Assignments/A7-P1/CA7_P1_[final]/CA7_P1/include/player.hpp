#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

const int TOTAL_WEEKS = 19;

class Player{
    private:
        std::string name;
        std::string role;
        //////////////////////////////////
        std::vector<float> scores;
        std::vector<bool> injureds;
        std::vector<bool> yellowCards;
        std::vector<bool> redCards;



    
    public:
        Player(std::string _name, std::string _role);
        std::string getName();
        std::string getRole();
        //////////////////////////////////
        std::vector<float> getScores();
        std::vector<bool> getInjureds();
        std::vector<bool> getYellowCards();
        std::vector<bool> getRedCards();
        //////////////////////////////////
        void setScoreAtWeek(float _score, int week);
        void setInjuredAtWeek(int week);
        void setYellowCardAtWeek(int week);
        void setRedCardAtWeek(int week);
        //////////////////////////////////
        float calcScoreTillWeek(int week);
        float getScoreOnWeek(int week);
        bool isAvailable(int week);

};

#endif