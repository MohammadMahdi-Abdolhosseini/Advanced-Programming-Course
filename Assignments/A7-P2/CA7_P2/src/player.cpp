#include "../include/player.hpp"

using namespace std;

Player::Player(string _name, string _role, int _cost) : scores(TOTAL_WEEKS, 0.0f),
                                             injureds(TOTAL_WEEKS, false),
                                             yellowCards(TOTAL_WEEKS, false),
                                             redCards(TOTAL_WEEKS, false),
                                             goals(TOTAL_WEEKS, 0),
                                             ownGoals(TOTAL_WEEKS, 0),
                                             assists(TOTAL_WEEKS, 0),
                                             posts(TOTAL_WEEKS, 0),
                                             cleanSheets(TOTAL_WEEKS, 0)
{
    name = _name;
    role = _role;
    cost = _cost;
}


string Player::getName(){
    return name;
}

string Player::getRole(){
    return role;
}

int Player::getCost(){
    return cost;
}

vector<float> Player::getScores(){
    return scores;
}

vector<bool> Player::getInjureds(){
    return injureds;
}

vector<bool> Player::getYellowCards(){
    return yellowCards;
}

vector<bool> Player::getRedCards(){
    return redCards;
}

vector<int> Player::getGoals(){
    return goals;
}

vector<int> Player::getOwnGoals(){
    return ownGoals;
}

vector<int> Player::getAssists(){
    return assists;
}

vector<int> Player::getPosts(){
    return posts;
}

vector<int> Player::getCleanSheets(){
    return cleanSheets;
}

void Player::addScoreAtWeek(float _score, int week){
    scores[week] += _score;
}

void Player::setScoreAtWeek(float _score, int week){
    scores[week] = _score;
}

void Player::setInjuredAtWeek(int week){
    injureds[week] = true;
}

void Player::setYellowCardAtWeek(int week){
    yellowCards[week] = true;
}

void Player::setRedCardAtWeek(int week){
    redCards[week] = true;
}

void Player::setGoalAtWeek(int week){
    goals[week]++;
}

void Player::setOwnGoalAtWeek(int week){
    ownGoals[week]++;
}

void Player::setAssistAtWeek(int week){
    assists[week]++;
}

void Player::setPostAtWeek(int _post, int week){
    posts[week] = _post;
}

void Player::setCleanSheetAtWeek(int week){
    cleanSheets[week] = 1;
}

float Player::calcScoreTillWeek(int week){
    float result = 0.0f;

    int count = 0;
    for(int i = 0; i < week + 1; i++){
        if (scores[i] != 0)
        {
            result += scores[i];
            count++;
        }
        
    }

    if (count == 0)
    {
        count++;
    }

    return result / count;
}

int Player::calcGoalTillWeek(int week){
    int result = 0;

    for(int i = 0; i < week + 1; i++){
        result += goals[i];
    }

    return result;
}

int Player::calcAssistTillWeek(int week){
    int result = 0;

    for(int i = 0; i < week + 1; i++){
        result += assists[i];
    }

    return result;
}

int Player::calcCleanSheetTillWeek(int week){
    int result = 0;

    for(int i = 0; i < week + 1; i++){
        result += cleanSheets[i];
    }

    return result;
}

float Player::getScoreOnWeek(int week){
    return scores[week];
}

bool Player::isAvailable(int week){
    for (int i = 1; i < 4; i++)
    {
        if (week - i > -1)
        {
            if (getInjureds()[week - i])
            {
                return false;
            }     
        }
    }

    if (week - 1 > -1)
    {
        if (getRedCards()[week - 1])
        {
            return false;
        }
    }

    int count = 0;
    for (int i = 0; i < week; i++)
    {
        if (getYellowCards()[i])
        {
            count++;
        }
        if (count == 3)
        {
            if (i == week - 1)
            {
                return false;
            }
            count = 0;              
        }      
    }
    
    return true;
}