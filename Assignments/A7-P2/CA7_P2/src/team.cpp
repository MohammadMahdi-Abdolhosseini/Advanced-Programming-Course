#include "../include/team.hpp"

using namespace std;

Team::Team(string _name){
    name = _name;
}

vector<string> Team::parseString(string& input, char by = ';') {
    vector<string> result;
    stringstream ss(input);
    string item;
    while (getline(ss, item, by)) {
        result.push_back(item);
    }
    return result;
}

Team::Team(string _name, vector<string> GoalKeepers, vector<string> defenders, vector<string> midFielders, vector<string> forwards){
    name = _name;
    for(auto gk : GoalKeepers){
        string name = parseString(gk, ':')[0];
        int cost = stoi(parseString(parseString(gk, ':')[1], '$')[0]);
        Player* p = new Player(name, "gk", cost);
        players.push_back(p);
    }
    for(auto gk : defenders){
        string name = parseString(gk, ':')[0];
        int cost = stoi(parseString(parseString(gk, ':')[1], '$')[0]);
        Player* p = new Player(name, "df", cost);
        players.push_back(p);
    }
    for(auto gk : midFielders){
        string name = parseString(gk, ':')[0];
        int cost = stoi(parseString(parseString(gk, ':')[1], '$')[0]);
        Player* p = new Player(name, "md", cost);
        players.push_back(p);
    }
    for(auto gk : forwards){
        string name = parseString(gk, ':')[0];
        int cost = stoi(parseString(parseString(gk, ':')[1], '$')[0]);
        Player* p = new Player(name, "fw", cost);
        players.push_back(p);
    }
}

string Team::getName(){
    return name;
}

void Team::printPlayer(Player* p, int week){
    cout << "name: " << p->getName();
    cout << " | role: " << p->getRole();
    cout << " | score: " << round(p->calcScoreTillWeek(week) * 10) / 10;
    cout << " | cost: " << p->getCost();
    if (p->getRole() != "gk"){
        cout << " | goals: " << p->calcGoalTillWeek(week);
        cout << " | assists: " << p->calcAssistTillWeek(week);
    }
    if (p->getRole() != "fw"){
        cout << " | clean sheets: " << p->calcCleanSheetTillWeek(week);
    }
    cout << endl;
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
                printPlayer(p, week);
                index ++;
            }
        }
        else
        {
            cout<< index << ". ";
            printPlayer(p, week);
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