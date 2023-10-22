#include "../include/user.hpp"

using namespace std;

User::User(string _userName, string _passWord){
    userName = _userName;
    password = _passWord;
}

string User::getUserName(){
    return userName;
}

string User::getPassWord(){
    return password;
}

Admin::Admin() : User("admin","123456"){

}


bool Admin::isAdmin(){
    return true;
}

RegularUser::RegularUser(string _userName, string _passWord):User(_userName, _passWord){
    fantasyTeam = new FantasyTeam(_userName);
} 

void RegularUser::addPlayer(Player* player, int week){
    if(player->getRole() == "df" && getRoleCount(player->getRole()) > 1){
        throw Bad_Request_Error();
    }
    else if(getRoleCount(player->getRole()) > 0 && player->getRole() != "df"){
        throw Bad_Request_Error();
    }
    else if(!player->isAvailable(week))
    {
        cout << "This player is not available for next week" << endl;
    }
    else if(player->getCost() > budget)
    {
        throw Bad_Request_Error();
    }
    else {
        budget -= player->getCost();
        fantasyTeam->addPlayer(player);
    }
    
}

int RegularUser::getRoleCount(std::string role){
    int count = 0;
    for(auto p: fantasyTeam->getPlayers()){
        if(p->getRole() == role){
            count ++;
        }
    }
    return count;
}

vector<Player*> RegularUser::getPlayerByRole(std::string role){
    vector<Player*> result;
    for(auto p : fantasyTeam->getPlayers()){
        if(p->getRole() == role){
            result.push_back(p);
        }
    }
    return result;
}

void RegularUser::printSquad(){
    if (fantasyTeam->getPlayers().size() < 5){
        throw Empty_Error();
    }
    
    cout << "fantasy_team: " << fantasyTeam->getName() << endl;
    cout << "Goalkeeper: " << getPlayerByRole("gk")[0]->getName();
    (captain == getPlayerByRole("gk")[0])? cout << " (CAPTAIN)" << endl : cout << endl;

    cout << "Defender1: " << getPlayerByRole("df")[0]->getName();
    (captain == getPlayerByRole("df")[0])? cout << " (CAPTAIN)" << endl : cout << endl;

    cout << "Defender2: " << getPlayerByRole("df")[1]->getName();
    (captain == getPlayerByRole("df")[1])? cout << " (CAPTAIN)" << endl : cout << endl;

    cout << "Midfielder: " << getPlayerByRole("md")[0]->getName();
    (captain == getPlayerByRole("md")[0])? cout << " (CAPTAIN)" << endl : cout << endl;

    cout << "Striker: " << getPlayerByRole("fw")[0]->getName();
    (captain == getPlayerByRole("fw")[0])? cout << " (CAPTAIN)" << endl : cout << endl;

    cout << "Total Points: " << getTotalPoints() << endl;

    cout << "Team Cost: " << getTeamCost() << endl;

}

float RegularUser::getTotalPoints(){
    return totalPoints;
}

void RegularUser::updateTotalPoints(int week){
    if (fantasyTeam->getPlayers().size() < 5)
    {
        return;
    }
    for (auto p : fantasyTeam->getPlayers())
    {
        totalPoints += p->getScores()[week];
        if (p == captain){
            totalPoints += p->getScores()[week];
        }
    }
    playersRemovedThisWeek = 0;
    isNewUser = false;
}

int RegularUser::getTeamCost(){
    int teamCost = 0;
    for (auto p : fantasyTeam->getPlayers())
    {
        teamCost += p->getCost();
    }
    return teamCost;
}

void RegularUser::removePlayer(string name){
    if(playersRemovedThisWeek == 2 && !isNewUser){
        throw Permission_Error();
    }
    Player* p = fantasyTeam->getPlayer(name);
    if(p == NULL){
        throw Not_Found_Error();
    }
    fantasyTeam->removePlayer(p);
    playersRemovedThisWeek ++;
    budget += p->getCost();

}

void RegularUser::printBudget(){
    cout << budget << endl;
}

void RegularUser::setCaptein(string name){

    Player* p = fantasyTeam->getPlayer(name);

    if (p == NULL) {
        throw Not_Found_Error();
    }
    
    captain = p;
}
