#include "../include/team.hpp"

using namespace std;

Team::Team(string _name){
    name = _name;
}

Team::Team(string _name, vector<string> GoalKeepers, vector<string> defenders, vector<string> midFielders, vector<string> forwards){
    name = _name;
    for(auto gk : GoalKeepers){
        Player* p = new Player(gk, "gk");
        players.push_back(p);
    }
    for(auto gk : defenders){
        Player* p = new Player(gk, "df");
        players.push_back(p);
    }
    for(auto gk : midFielders){
        Player* p = new Player(gk, "md");
        players.push_back(p);
    }
    for(auto gk : forwards){
        Player* p = new Player(gk, "fw");
        players.push_back(p);
    }
}

string Team::getName(){
    return name;
}

void Team::printPlayers(int week, string filter, bool ranked){
    cout<<"list of players :"<<endl;
    int index = 1;

    if(ranked){
        sort(players.begin(), players.end(), [week](Player* a, Player* b) {
            return Team::sortByScore(a, b, week);
        });
    }
    else{
        sort(players.begin(), players.end(), sortByName); 
    }
    

    for(auto p : players){

        if(filter != "all"){
            if(p->getRole() == filter){
                cout<< index << ". ";
                cout << "name: " << p->getName();
                cout << " | role: " << p->getRole();
                cout << " | score: " << p->calcScoreTillWeek(week) << endl;
                index ++;
            }
        }
        else
        {
            cout<< index << ". ";
            cout << "name: " << p->getName();
            cout << " | role: " << p->getRole();
            cout << " | score: " << p->calcScoreTillWeek(week) << endl;
            index ++;
        }
    }
}

vector<int> Team::getScores(){
    return scores;
}

vector<int> Team::getGFs(){
    return GFs;
}

vector<int> Team::getGAs(){
    return GAs;
}

void Team::addScore(int _score){
    scores.push_back(_score);
}

void Team::addGF(int _GF){
    GFs.push_back(_GF);
}

void Team::addGA(int _GA){
    GAs.push_back(_GA);
}

Player* Team::getPlayer(string playerName){
    for(auto p : players){
        if(p->getName()  == playerName){
            return p;
        }
    }
    return NULL;
}

int Team::calcScoreTillWeek(int week){
    int result = 0;
    for(int i = 0; i < week + 1; i++){
        result += scores[i];
    }
    return result;
}

int Team::calcGoalForTillWeek(int week){
    int result = 0;
    for(int i = 0; i < week + 1; i++){
        result += GFs[i];
    }
    return result;
}


int Team::calcGoalAgainstTillWeek(int week){
    int result = 0;
    for(int i = 0; i < week + 1; i++){
        result += GAs[i];
    }
    return result;
}

bool Team::sortByScore(Player* a, Player* b, int currentWeek) {
    if (a->calcScoreTillWeek(currentWeek) == b->calcScoreTillWeek(currentWeek))
    {
        return sortByName(a, b);
    }
    else
    {
        return a->calcScoreTillWeek(currentWeek) > b->calcScoreTillWeek(currentWeek);
    }   
}

bool Team::sortByName(Player* a, Player* b) {
    return a->getName() < b->getName();
}

vector<Player*> Team::getPlayers(){
    sort(players.begin(), players.end(), sortByName);
    return players;
}

FantasyTeam::FantasyTeam(std::string name):Team(name){

}

void FantasyTeam::addPlayer(Player* player){
    players.push_back(player);
}

void FantasyTeam::removePlayer(Player* player){
    for (auto it = players.begin(); it != players.end(); ++it) {
        if (*it == player) {
            players.erase(it);
            break;
        }
    }
}