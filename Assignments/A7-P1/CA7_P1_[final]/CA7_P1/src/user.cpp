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
    else {
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
    cout << "Goalkeeper: " << getPlayerByRole("gk")[0]->getName() << endl;
    cout << "Defender1: " << getPlayerByRole("df")[0]->getName() << endl;
    cout << "Defender2: " << getPlayerByRole("df")[1]->getName() << endl;
    cout << "Midfielder: " << getPlayerByRole("md")[0]->getName() << endl;
    cout << "Striker: " << getPlayerByRole("fw")[0]->getName() << endl;
    cout << "Total Points: " << getTotalPoints() << endl;
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
    }
    playersRemovedThisWeek = 0;
    isNewUser = false;
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

}
