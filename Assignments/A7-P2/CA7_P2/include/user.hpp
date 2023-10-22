#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


#include "../include/team.hpp"
#include "../include/Errors.hpp"



class User{
    protected:
        std::string userName;
        std::string password;



    
    public:
        User(std::string _userName,std::string _passWord);
        virtual std::string getUserName();
        virtual std::string getPassWord();



};

class Admin : public User {
    public:
        Admin();  
        virtual bool isAdmin();
    private:

};

class RegularUser : public User {
    public:
        RegularUser(std::string _userName,std::string _passWord);
        void addPlayer(Player* player, int week);
        int getRoleCount(std::string role);
        std::vector<Player*> getPlayerByRole(std::string role);
        void printSquad();
        float getTotalPoints();
        void updateTotalPoints(int week);
        void removePlayer(std::string);
        void printBudget();
        void setCaptein(std::string name);
        int getTeamCost();

    private:
        FantasyTeam* fantasyTeam;
        float totalPoints = 0.0f;
        int playersRemovedThisWeek = 0;
        bool isNewUser = true;
        int budget = 2500;
        Player* captain;

};

#endif