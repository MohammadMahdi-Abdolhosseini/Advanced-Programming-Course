#if !defined(__GAME__)
#define __GAME__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "../include/player.hpp"
#include "../include/map.hpp"
#include "../include/platform.hpp"
#include "../include/enemy.hpp"
#include "../include/levelConfigs.hpp"

class Game
{
public:
Game();

const sf::RenderWindow& getWindow() const;

void update();
void render();


private:
sf::RenderWindow window;
sf::View view;
void initWindow();
void drawScore(int score);
void gameOverCheck();
void babyCollisionWithPortalHandler();
void drawRemainingBaby(int remainingBaby);
void drawLevel(int lvl);
void loadLevel();
int currLevel = 0;


Player *player;
Map *map;


};

#endif // __GAME__