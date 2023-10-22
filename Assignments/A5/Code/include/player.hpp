#if !defined(__PLAYER__)
#define __PLAYER__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "../include/map.hpp"

class Player{

public:
Player(float x, float y);

void update(float deltaTime, Map& map);
void draw(sf::RenderWindow& window);
void setMovingLeft(bool movingLeft);
void setMovingRight(bool movingRight);
void jump();
void reset();
void setOrigPos(sf::Vector2f spawnPoint);
void setWinState(int state);
void setScore(int score);
sf::Sprite& getSprite();
int getScore();
int getWinState();
void gotHurt();
void toggleGodMode();

private:
sf::Texture texture;
sf::Sprite m_sprite;
float m_speed = 20;
float m_jumpSpeed = 70;
float m_gravity = 9.8;
sf::Vector2f m_velocity{0, 0};
sf::Vector2f m_newPosition;
bool m_movingLeft = false;
bool m_movingRight = false;
bool m_jumping = false;
int m_score = 0;
int m_health = 3;
int m_winState = 0;
const std::string H3_TEXTURE_DIR = "./pictures/player.png";
const std::string H2_TEXTURE_DIR = "./pictures/sad-player.png";
const std::string H1_TEXTURE_DIR = "./pictures/mad-player.png";
const std::string H0_TEXTURE_DIR = "./pictures/dead-player.png";

float origPosX;
float origPosY;

bool collisionWithTop = false;
bool collisionWithRight = false;
bool collisionWithLeft = false;
bool collisionWithBottom = false;

void platformsCollisionHandler (std::vector<Platform>& platforms);
void itemsCollisionHandler(std::vector<Item>& items);
void enemiesCollisionHandler(std::vector<Enemy>& enemies);
void gameOverHandler(Map& map);
void babiesCollisionHandler (std::vector<Baby>& babies);
void tiqsCollisionHandler (std::vector<Tiq>& tiqs);
void updateHealthTexture();

bool godMode = false;
bool firstTime = true;

};

#endif