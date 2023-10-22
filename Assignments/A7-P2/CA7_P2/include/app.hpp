#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <unordered_set>
#include <cmath>
#include <iomanip>
#include <algorithm>

#include "../include/team.hpp"
#include "../include/user.hpp"
#include "Errors.hpp"

const std::string SUCCESSFUL = "OK\n";
const int WIN_SCORE = 3;
const int DRAW_SCORE = 1;
const int LOSS_SCORE = 0;

enum Roles { GOALKEEPER = 0,
             SIDE_LEFT_DEFENDER = 1,
             MID_LEFT_DEFENDER = 2,
             MID_RIGHT_DEFENDER = 3,
             SIDE_RIGHT_DEFENDER = 4,
             LEFT_MIDFIELDER= 5,
             MID_MIDFIELDER = 6,
             RIGHT_MIDFIELDER = 7,
             LEFT_STRIKER = 8,
             MID_STRIKER = 9,
             RIGHT_STRIKER = 10 };

class App{
    private:
        const std::string LEAGUE_ADDRESS = "data/premier_league.csv";
        const std::string PARTIAL_WEEKS_STATS_ADDRESS = "data/weeks_stats/week_";

        std::vector<std::string> splitToWords(std::string line);
        std::vector<Team*> teams;
        std::vector<std::vector<std::string>> readCSV(std::string filename);
        std::vector<std::string> parseString(std::string& input, char by);
        std::string replaceSpacesWithUnderscores(std::string input); 
        bool isTransferWindowOpen = true;


        void GETrequest(std::vector<std::string> words);
        void POSTrequest(std::vector<std::string> words);
        void PUTrequest(std::vector<std::string> words);
        void DELETErequest(std::vector<std::string> words);


        /////////////////////////////////////////////////////////////////////////
        std::vector <User*> users;
        User* loggedUser = nullptr;

        void registerAdmin(std::string username, std::string password);
        void signUp(std::string username, std::string password);
        void logIn(std::string username, std::string password);
        User* getUser(std::string username);
        void logOut();

        void setTransferWindowOpen(bool status);
        //////////////////////////////////////////////////////////////////////////

        Team* getTeam(std::string teamName, bool hasUnderscore);
        void showTeamByName(std::vector<std::string> arguments);
        void showLeagueStanding();
        static bool sortByScore(Team* a, Team* b, int currentWeek);
        void teamOfTheWeek(std::vector<std::string> command);
        std::vector<Player*> getBestPlayersOfRole(int week, std::string role , int count = 1);
        std::string vectorToString(const std::vector<std::string>& words);
        void printSquad(std::vector<std::string> command);
        void usersRanking();
        static bool sortByFantasyName(RegularUser* a, RegularUser* b);

        Player* getPlayer(std::string playerName);

        void initTeams();
        void initWeeks();
        void printTeams();

        int calcScore(int g1, int g2);
        void saveMatchResult(std::vector<std::string> match, std::vector<std::string> result);
        void saveInjureds(std::vector<std::string> _injureds, int week);
        void saveYellowCards(std::vector<std::string> _yellowCards, int week);
        void saveRedCards(std::vector<std::string> _redCards, int week);
        void savePlayersScore(std::vector<std::string> team1, std::vector<std::string> team2, std::vector<std::string> result, int week);
        void showMatchResultOnWeek(std::vector<std::string> command);
        void buyPlayer(std::string name);
        void sellPlayer(std::string name);
        void saveGoalwithAssist(std::vector<std::string> _goalwithAssist, int week);
        void savePlayersPost(std::vector<std::string> team1, std::vector<std::string> team2, int week);

        void addWinStateScore(std::vector<Player*> team1players, std::vector<Player*> team2players, std::vector<std::string> result, int week);
        void handleGKScore(std::vector<Player*> team1players, std::vector<Player*> team2players, std::vector<std::string> result, int week);
        void handleDFScore(std::vector<Player*> team1players, std::vector<Player*> team2players, std::vector<std::string> result, int week);
        void handleMDScore(std::vector<Player*> team1players, std::vector<Player*> team2players, std::vector<std::string> result, int week);
        void handleFWScore(std::vector<Player*> team1players, std::vector<Player*> team2players, int week);
        void handleOwnGoalScore(std::vector<Player*> team1players, std::vector<Player*> team2players, int week);
        void handleOpponent(std::vector<Player*> team1players, std::vector<Player*> team2players, int week);
        void handleAx(std::vector<Player*> team1players, std::vector<Player*> team2players, int week);

        void showBudget();
        void setCaptain(std::string name);

        int currentWeek = -1;
        void passWeek();

    
    public:
        App();
        
        // Public methods
        void start();
        void commandHandler();

};