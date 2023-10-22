#include "../include/map.hpp"

using namespace std;

Map::Map()
{
    if (!platformTexture.loadFromFile(PLATFORM_TEXTURE_DIR))
        cerr << "CANT LOAD PLATFORM TEXTURE" << PLATFORM_TEXTURE_DIR << endl;
        
    if (!coinTexture.loadFromFile(COIN_TEXTURE_DIR))
        cerr << "CANT LOAD COIN TEXTURE" << COIN_TEXTURE_DIR << endl;

    if (!diomondTexture.loadFromFile(DIOMOND_TEXTURE_DIR))
        cerr << "CANT LOAD DIOMOND TEXTURE" << DIOMOND_TEXTURE_DIR << endl;

    if (!enemyTexture.loadFromFile(ENEMY_TEXTURE_DIR))
        cerr << "CANT LOAD ENEMY TEXTURE" << ENEMY_TEXTURE_DIR << endl;

    if (!wildEnemyTexture.loadFromFile(WILD_ENEMY_TEXTURE_DIR))
        cerr << "CANT LOAD WILD ENEMY TEXTURE" << WILD_ENEMY_TEXTURE_DIR << endl;

    if (!portalTexture.loadFromFile(PORTAL_TEXTURE_DIR))
        cerr << "CANT LOAD PORTAL TEXTURE" << PORTAL_TEXTURE_DIR << endl;

    if (!bubbleBabyTexture.loadFromFile(BUBBLE_BABY_TEXTURE_DIR))
        cerr << "CANT LOAD BUBBLE BABY TEXTURE" << BUBBLE_BABY_TEXTURE_DIR << endl;

    if (!babyTexture.loadFromFile(BABY_TEXTURE_DIR))
        cerr << "CANT LOAD BABY TEXTURE" << BABY_TEXTURE_DIR << endl;

    if (!tiqTexture.loadFromFile(TIQ_TEXTURE_DIR))
        cerr << "CANT LOAD TIQ TEXTURE" << TIQ_TEXTURE_DIR << endl;

    if (!font.loadFromFile(FONT_DIR)) {
        cerr << "CANT LOAD FONT" << FONT_DIR << endl;
    }

}

void Map::loadMap(const char levelMap[][MAP_WIDTH]){
    platforms.clear();
    tiqs.clear();
    coins.clear();
    diomonds.clear();
    enemies.clear();
    for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
        char tileChar = levelMap[y][x];
        if (tileChar == '#'){
            addPlatformAtPosition({float(TILE_SIZE*x), float(TILE_SIZE*y)});
        }
        else if(tileChar == 'c'){
            addCoinAtPosition({float(TILE_SIZE*x), float(TILE_SIZE*y)});
        }
        else if(tileChar == 'd'){
            addDiomondAtPosition({float(TILE_SIZE*x), float(TILE_SIZE*y)});
        }
        else if(tileChar == 'e'){
            addEnemyAtPosition({float(TILE_SIZE*x), float(TILE_SIZE*y)}, 1);
        }
        else if(tileChar == 'm'){
            addEnemyAtPosition({float(TILE_SIZE*x), float(TILE_SIZE*y)}, 2);
        }
        else if(tileChar == 'p'){
            portal = new Portal(portalTexture, {float(TILE_SIZE*x), float(TILE_SIZE*y)});
        }
        else if(tileChar == 'b'){
            addBabyAtPosition({float(TILE_SIZE*x), float(TILE_SIZE*y)});
        }
        else if (tileChar == 't'){
            addTiqAtPosition({float(TILE_SIZE*x), float(TILE_SIZE*y)});
        }
    }
}
}

void Map::draw(sf::RenderWindow& window)
{
    for (const auto& platform : platforms)
    {
        platform.draw(window);
    }
    for (const auto& coin : coins)
    {
        coin.draw(window);
    }
    for (const auto& diomond : diomonds)
    {
        diomond.draw(window);
    }
    for (const auto& enemy : enemies)
    {
        enemy.draw(window);
    }
    for (const auto& enemy : enemies)
    {
        enemy.draw(window);
    }
    for (const auto& baby : babies)
    {
        baby.draw(window);
    }
    for (const auto& tiq : tiqs)
    {
        tiq.draw(window);
    }
    portal->draw(window);  
}

void Map::addPlatformAtPosition(sf::Vector2f position)
{
    Platform platform(platformTexture, position);
    platforms.push_back(platform);
}

void Map::addCoinAtPosition(sf::Vector2f position)
{
    Item coin(coinTexture, position, COIN_SCORE);
    coins.push_back(coin);
}

void Map::addDiomondAtPosition(sf::Vector2f position)
{
    Item diomond(diomondTexture, position, DIOMOND_SCORE);
    diomonds.push_back(diomond);
}

void Map::addEnemyAtPosition(sf::Vector2f position, int type)
{
    if (type == 1){
        Enemy enemy(enemyTexture, position, type);
        enemies.push_back(enemy);
    }
    else if (type == 2){
        Enemy enemy(wildEnemyTexture, position, type);
        enemies.push_back(enemy);
    }   
}

void Map::addBabyAtPosition(sf::Vector2f position)
{
    Baby baby(bubbleBabyTexture, position, babyTexture);
    babies.push_back(baby);
}

void Map::addTiqAtPosition(sf::Vector2f position)
{
    Tiq tiq(tiqTexture, position);
    tiqs.push_back(tiq);
}


std::vector<Platform>& Map::getPlatforms()
{
    return platforms;
}

std::vector<Item>& Map::getCoins()
{
    return coins;
}

std::vector<Item>& Map::getDiomonds()
{
    return diomonds;
}

std::vector<Enemy>& Map::getEnemies()
{
    return enemies;
}

Portal& Map::getPortal()
{
    return *portal;
}

std::vector<Baby>& Map::getBabies()
{
    return babies;
}

std::vector<Tiq>& Map::getTiqs()
{
    return tiqs;
}

sf::Font& Map::getFont(){
    return font; 
}