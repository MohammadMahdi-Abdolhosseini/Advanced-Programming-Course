#include "../include/player.hpp"

using namespace std;

Player::Player(string _name, string _role) : scores(TOTAL_WEEKS, 0.0f),
                                             injureds(TOTAL_WEEKS, false),
                                             yellowCards(TOTAL_WEEKS, false),
                                             redCards(TOTAL_WEEKS, false)
{
    name = _name;
    role = _role;
}


string Player::getName(){
    return name;
}

string Player::getRole(){
    return role;
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