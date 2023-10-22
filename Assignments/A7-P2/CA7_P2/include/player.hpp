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
        int cost;
        //////////////////////////////////
        std::vector<float> scores;
        std::vector<bool> injureds;
        std::vector<bool> yellowCards;
        std::vector<bool> redCards;
        std::vector<int> goals;
        std::vector<int> ownGoals;
        std::vector<int> assists;
        std::vector<int> posts;
        std::vector<int> cleanSheets;


    
    public:
        Player(std::string _name, std::string _role, int _cost);
        std::string getName();
        std::string getRole();
        int getCost();
        //////////////////////////////////
        std::vector<float> getScores();
        std::vector<bool> getInjureds();
        std::vector<bool> getYellowCards();
        std::vector<bool> getRedCards();
        std::vector<int> getGoals();
        std::vector<int> getOwnGoals();
        std::vector<int> getAssists();
        std::vector<int> getPosts();
        std::vector<int> getCleanSheets();
        //////////////////////////////////
        void addScoreAtWeek(float _score, int week);
        void setScoreAtWeek(float _score, int week);
        void setInjuredAtWeek(int week);
        void setYellowCardAtWeek(int week);
        void setRedCardAtWeek(int week);
        void setGoalAtWeek(int week);
        void setOwnGoalAtWeek(int week);
        void setAssistAtWeek(int week);
        void setPostAtWeek(int _post, int week);
        void setCleanSheetAtWeek(int week);
        //////////////////////////////////
        float calcScoreTillWeek(int week);
        float getScoreOnWeek(int week);
        bool isAvailable(int week);
        int calcGoalTillWeek(int week);
        int calcAssistTillWeek(int week);
        int calcCleanSheetTillWeek(int week);

};

#endif