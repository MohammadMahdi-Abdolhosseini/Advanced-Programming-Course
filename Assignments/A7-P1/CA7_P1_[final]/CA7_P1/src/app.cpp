#include "../include/app.hpp"

using namespace std;

App::App() {

}

void App::start(){
    Admin* a = new Admin;
    users.push_back(a);

    initTeams();
    initWeeks();
    commandHandler();
}

vector<string> App::splitToWords(string line)
{
	vector<string> words;
	stringstream sLine(line);
	string word;
	while (sLine >> word)
	{
		words.push_back(word);
	}
	return words;
}

string App::replaceSpacesWithUnderscores(string input) {
    for (size_t i = 0; i < input.length(); i++) {
        if (input[i] == ' ') {
            input[i] = '_';
        }
    }
    return input;
}

void App::commandHandler(){
    string line;
	while (getline(cin, line))
	{
        try{
            vector<string> words = splitToWords(line);
            vector<string> command(words.begin() + 1, words.end());

            if (words[0] == "GET")
		    {
			    GETrequest(command);
		    }   
            else if (words[0] == "POST")
		    {
			    POSTrequest(command);
                cout<< SUCCESSFUL;
		    }   
            else if (words[0] == "PUT")
		    {
			    PUTrequest(command);
                cout<< SUCCESSFUL;
		    }   
            else if (words[0] == "DELETE")
		    {
			    DELETErequest(command);
                cout<< SUCCESSFUL;
		    }   
		    else
		    {
			    throw Bad_Request_Error();
		    }
        }
        catch (Permission_Error& p) {
			cout << p.what();
		}
		catch (Bad_Request_Error& b) {
			cout << b.what();
		}
		catch (Not_Found_Error& n) {
			cout << n.what();
		}
        catch (Empty_Error& e) {
			cout << e.what();
		}
        catch (std::length_error& l){
            cout << "\\[-_-]/" << endl;
        }

	}
}

void App::GETrequest(vector<string> command){
    if(command[0] == "players"){
        showTeamByName(command);
    }
    else if(command[0] == "league_standings"){
        showLeagueStanding();
    }
    else if(command[0] == "team_of_the_week"){
        teamOfTheWeek(command);
    }
    else if(command[0] == "matches_result_league"){
        showMatchResultOnWeek(command);
    }
    else if (command[0] == "squad"){
        printSquad(command);
    }
    else if (command[0] == "users_ranking"){
        usersRanking();
    }
    else
    {
        throw Not_Found_Error();
    }
}

void App::POSTrequest(vector<string> command){
    if(command[0] == "signup"){
        signUp(command[3], command[5]);
    }
    else if(command[0] == "login"){
        logIn(command[3], command[5]);
    }
    else if(command[0] == "register_admin"){
        registerAdmin(command[3], command[5]);
    }
    else if(command[0] == "logout"){
        logOut();
    }
    else if(command[0] == "buy_player"){
        vector<string> name(command.begin() + 3, command.end());
        buyPlayer(vectorToString(name));
    }
    else if(command[0] == "sell_player"){
        vector<string> name(command.begin() + 3, command.end());
        sellPlayer(vectorToString(name));
    }
    else if(command[0] == "close_transfer_window"){
        setTransferWindowOpen(false);
    }
    else if(command[0] == "open_transfer_window"){
        setTransferWindowOpen(true);
    }
    else if(command[0] == "pass_week"){
        passWeek();
    }
    else
    {
        throw Not_Found_Error();
    }
}

void App::PUTrequest(vector<string> command){

}

void App::DELETErequest(vector<string> command){

}


vector<vector<string>> App::readCSV(string filename) {
	vector<vector<string>> data;
	ifstream file(filename);

	if (!file.is_open()) {
		cout << "Error opening file" << endl;
		return data;
	}

	string line;

	while (getline(file, line)) {
		stringstream ss(line);
		vector<string> row;

	    while (getline(ss, line, ',')) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            row.push_back(line);
        }

		data.push_back(row);
	}

	file.close();
	return data;
}

vector<string> App::parseString(string& input, char by = ';') {
    vector<string> result;
    stringstream ss(input);
    string item;
    while (getline(ss, item, by)) {
        result.push_back(item);
    }
    return result;
}


void App::initTeams(){
    vector<vector<string>> data = readCSV(LEAGUE_ADDRESS);
    for(int line = 1; line < data.size(); line++){

        Team* t = new Team(data[line][0],parseString(data[line][1]),parseString(data[line][2]),parseString(data[line][3]),parseString(data[line][4]));
        teams.push_back(t);

    }

}

void App::printTeams(){
    for(auto t : teams){
        cout << "Team Name: " << t->getName() << endl;;
        t->printPlayers(currentWeek);
        cout<<"=================================="<<endl;
    }
}

void App::signUp(string username, string password){
    for(auto u : users){
        if(u->getUserName() == username){
            throw Bad_Request_Error();
        }
    }
    RegularUser* u = new RegularUser(username, password);
    users.push_back(u);
    loggedUser = u;
}

void App::registerAdmin(string username, string password){
    User* a = getUser(username);
    if(a->getPassWord() == password && dynamic_cast<Admin*>(a)){
        loggedUser = a;
    }
    else {
        throw Permission_Error();
    }

    
}

void App::logIn(string username, string password){
    
    User* a = getUser(username);

    if(dynamic_cast<Admin*>(a)){
        throw Permission_Error();
    }

    if(a->getPassWord() == password){
        loggedUser = a;
    }
    else{
        throw Permission_Error();
    }

}

void App::logOut(){
    loggedUser = nullptr;
}

User* App::getUser(string username){
    for(auto u : users){
        if(u->getUserName() == username){
            return u;
        }
    }

    throw Not_Found_Error();
}

void App::setTransferWindowOpen(bool status){
    if(loggedUser == nullptr) {
        throw Permission_Error();
    }
    if(!dynamic_cast<Admin*>(loggedUser)){
        throw Permission_Error();
    }

    isTransferWindowOpen = status;
}

Team* App::getTeam(string teamName, bool hasUnderscore = true){
    for(auto t : teams){
        if(replaceSpacesWithUnderscores(t->getName())  == teamName && hasUnderscore == true){
            return t;
        }
        if(t->getName()  == teamName && hasUnderscore == false){
            return t;
        }
    }
    throw Not_Found_Error();
}


void App::showTeamByName(vector<string> command){
    Team* t = getTeam(command[3]);
    string filter = "all";
    bool ranked = false;
    if(command.size() > 4){
        if(command[4] == "gk" || command[4] == "df" || command[4] == "md" || command[4] == "fw"){
            filter = command[4];
        }
        else if(command[4] == "ranks"){
            ranked = true;
        }
        else{
            throw Bad_Request_Error();
        } 
    }
    if(command.size() > 5){
        if(command[5] == "gk" || command[5] == "df" || command[5] == "md" || command[5] == "fw"){
            filter = command[5];
        }
        else if(command[5] == "ranks"){
            ranked = true;
        }
        else{
            throw Bad_Request_Error();
        } 
    }
    t->printPlayers(currentWeek, filter, ranked);

}

Player* App::getPlayer(string playerName){
    for(auto t : teams){
        Player* p = t->getPlayer(playerName);
        if (p != NULL){
            return p;
        }
    }
    return NULL;
}

void App::initWeeks(){
    for(int week = 0; week < TOTAL_WEEKS; week++){
        vector<vector<string>> data = readCSV(PARTIAL_WEEKS_STATS_ADDRESS + to_string(week + 1) + ".csv");
        for(int line = 1; line < data.size(); line++){

            saveMatchResult(parseString(data[line][0], ':'), parseString(data[line][1], ':'));
            saveInjureds(parseString(data[line][2]), week);
            saveYellowCards(parseString(data[line][3]), week);
            saveRedCards(parseString(data[line][4]), week);
            savePlayersScore(parseString(data[line][5]), week);

        }
    }
    
}

int App::calcScore(int g1, int g2){
    if (g1 > g2){
        return WIN_SCORE;
    }
    if (g1 == g2){
        return DRAW_SCORE;
    }
    return LOSS_SCORE;
}

void App::saveMatchResult(vector<string> match, vector<string> result){
    Team* team1 = getTeam(match[0], false);
    team1->addGF(stoi(result[0]));
    team1->addGA(stoi(result[1]));
    team1->addScore(calcScore(stoi(result[0]), stoi(result[1])));
    Team* team2 = getTeam(match[1], false);
    team2->addGF(stoi(result[1]));
    team2->addGA(stoi(result[0]));
    team2->addScore(calcScore(stoi(result[1]), stoi(result[0])));
}

void App::saveInjureds(vector<string> _injureds, int week){
    for(auto i : _injureds){
        Player* p = getPlayer(i);
        p->setInjuredAtWeek(week);
    }  
}

void App::saveYellowCards(vector<string> _yellowCards, int week){
    for(auto y : _yellowCards){
        Player* p = getPlayer(y);
        p->setYellowCardAtWeek(week);
    }
}

void App::saveRedCards(vector<string> _redCards, int week){
    for(auto r : _redCards){
        Player* p = getPlayer(r);
        p->setRedCardAtWeek(week);
    }
}

void App::savePlayersScore(vector<string> _playersScore, int week){
    for(auto s : _playersScore){
        vector<string> playerScore = parseString(s, ':');
        Player* p = getPlayer(playerScore[0]);
        p->setScoreAtWeek(stof(playerScore[1]), week);
    }
}

void App::passWeek(){
    if (!dynamic_cast<Admin*>(loggedUser))
    {
        throw Permission_Error();
    }

    currentWeek++;
    
    for (auto u : users){
        if (dynamic_cast<RegularUser*>(u))
        {
            dynamic_cast<RegularUser*>(u)->updateTotalPoints(currentWeek);
        }
    }
    
}

bool App::sortByScore(Team* a, Team* b, int currentWeek) {
    if (a->calcScoreTillWeek(currentWeek) == b->calcScoreTillWeek(currentWeek))
    {
        int difA = a->calcGoalForTillWeek(currentWeek) - a->calcGoalAgainstTillWeek(currentWeek);
        int difB = b->calcGoalForTillWeek(currentWeek) - b->calcGoalAgainstTillWeek(currentWeek);
        if (difA == difB)
        {
            if (a->calcGoalForTillWeek(currentWeek) == b->calcGoalForTillWeek(currentWeek))
            {
                return a->getName() < b->getName();
            }
            else
            {
                return a->calcGoalForTillWeek(currentWeek) > b->calcGoalForTillWeek(currentWeek); 
            }
        }
        else
        {
            return difA > difB;
        }
    }
    else
    {
        return a->calcScoreTillWeek(currentWeek) > b->calcScoreTillWeek(currentWeek);
    }    
}

void App::showLeagueStanding(){
    int week = currentWeek;
    sort(teams.begin(), teams.end(), [week](Team* a, Team* b) {
        return App::sortByScore(a, b, week);
    });
    int i = 1;
    for (auto team : teams){
        cout << i << ". " << team->getName() << ": score: " << team->calcScoreTillWeek(currentWeek);
        cout << " | GF: " << team->calcGoalForTillWeek(currentWeek);
        cout << " | GA: " << team->calcGoalAgainstTillWeek(currentWeek) << endl;           
        i++;
    }
}

void App::teamOfTheWeek(vector<string> command){


    int week = currentWeek;
    if(command.size() > 3){
        week = stoi(command[3]);
        if(week > currentWeek || week < 0){
            throw Bad_Request_Error();
        }
    }

    for(auto p : getBestPlayersOfRole(week, "gk")){
        cout << "GoalKeeper: " << p->getName() << " | " << "score: " << p->getScoreOnWeek(week) << endl;;
    }
    int i = 1;
    for(auto p : getBestPlayersOfRole(week, "df", 2)){
        cout << "Defender " << i << ": "<< p->getName() << " | " << "score: " << p->getScoreOnWeek(week) << endl;
        i++;
    }
    for(auto p : getBestPlayersOfRole(week, "md")){
        cout << "Midfielder: " << p->getName() << " | " << "score: " << p->getScoreOnWeek(week) << endl;
    }
    for(auto p : getBestPlayersOfRole(week, "fw")){
        cout << "Forward: " << p->getName() << " | " << "score: " << p->getScoreOnWeek(week) << endl;
    }
    

}

vector<Player*> App::getBestPlayersOfRole(int week, string role , int count){
    vector<Player*> result;
    for(int i = 0; i< count ; i++){
        float bestScore = 0.0f;
        Player* bestPlayer;
        for(auto t :teams){
            for(auto p : t->getPlayers()){
                if(p->getRole() == role && p->getScoreOnWeek(week) > bestScore && (find(result.begin(), result.end(), p) == result.end())){
                    bestScore = p->getScoreOnWeek(week);
                    bestPlayer = p;
                }
            }
        }
        result.push_back(bestPlayer);
    }
    return result;
}


void App::showMatchResultOnWeek(vector<string> command){

    int week = currentWeek + 1;
    if(command.size() > 3){
        week = stoi(command[3]);
        if(week > currentWeek || week < 0){
            throw Bad_Request_Error();
        }
    }

    vector<vector<string>> data = readCSV(PARTIAL_WEEKS_STATS_ADDRESS + to_string(week) + ".csv");
    for(int line = 1; line < data.size(); line++){
        vector<string> teamsName = parseString(data[line][0], ':');
        vector<string> matchResult = parseString(data[line][1], ':');
        cout << teamsName[0] << ' ' << matchResult[0] << " | " << teamsName[1] << ' ' << matchResult[1] << endl;
    }

}

string App::vectorToString(const vector<string>& words) {
    std::ostringstream oss;
    for (size_t i = 0; i < words.size(); ++i) {
        oss << words[i];
        if (i != words.size() - 1) {
            oss << " ";
        }
    }
    return oss.str();
}

 void App::buyPlayer(string name){
    Player* p =  getPlayer(name);
    if(p == NULL){
        throw Not_Found_Error();
    }
    if(isTransferWindowOpen == false || !dynamic_cast<RegularUser*>(loggedUser)){
        throw Permission_Error();
    }
    RegularUser* user = dynamic_cast<RegularUser*>(loggedUser);
    user->addPlayer(p, currentWeek);
 }

 void App::sellPlayer(string name){
    if(isTransferWindowOpen == false || !dynamic_cast<RegularUser*>(loggedUser)){
        throw Permission_Error();
    }
    dynamic_cast<RegularUser*>(loggedUser)->removePlayer(name);
}

 void App::printSquad(vector<string> command){
    if(!dynamic_cast<RegularUser*>(loggedUser)){
        throw Permission_Error();
    }
    RegularUser* user = dynamic_cast<RegularUser*>(loggedUser);
    if (command.size() > 3)
    {
        user = dynamic_cast<RegularUser*>(getUser(command[3]));
    }
    user->printSquad();
 }

bool App::sortByFantasyName(RegularUser* a, RegularUser* b){
    if (a->getTotalPoints() == b->getTotalPoints())
    {
        return a->getUserName() < b->getUserName();       
    }
    else
    {
        return a->getTotalPoints() > b->getTotalPoints();
    }
}


void App::usersRanking(){
    vector<RegularUser*> rusers;
    for (auto u : users)
    {
        if (dynamic_cast<RegularUser*>(u))
        {
            rusers.push_back(dynamic_cast<RegularUser*>(u));
        }
    }

    sort(rusers.begin(), rusers.end(), sortByFantasyName);

    int i = 1;
    for (auto r : rusers)
    {
        cout << i << ". team_name: " << r->getUserName() << " | point: " << r->getTotalPoints() << endl;
        i++;
    }

 }