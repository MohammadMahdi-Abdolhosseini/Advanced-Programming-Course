#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include "../include/platform.hpp"
#include "../include/item.hpp"
#include "../include/enemy.hpp"
#include "../include/portal.hpp"
#include "../include/baby.hpp"
#include "../include/tiq.hpp"


class Map {
public:
    Map();
    static const int MAP_WIDTH = 20;
    static const int MAP_HEIGHT = 10;

    void draw(sf::RenderWindow& window);
    void addPlatformAtPosition(sf::Vector2f position);
    void addCoinAtPosition(sf::Vector2f position);
    void addDiomondAtPosition(sf::Vector2f position);
    void addEnemyAtPosition(sf::Vector2f position, int type);
    void addBabyAtPosition(sf::Vector2f position);
    void addTiqAtPosition(sf::Vector2f position);

    std::vector<Platform>& getPlatforms();
    std::vector<Item>& getCoins();
    std::vector<Item>& getDiomonds();
    std::vector<Enemy>& getEnemies();
    Portal& getPortal();
    std::vector<Baby>& getBabies();
    std::vector<Tiq>& getTiqs();
    sf::Font& getFont();
    void loadMap(const char levelMap[][MAP_WIDTH]);
    
private:
    sf::Texture platformTexture;
    const std::string PLATFORM_TEXTURE_DIR = "./pictures/platform.png";
    std::vector<Platform> platforms;
    sf::Texture coinTexture;
    const std::string COIN_TEXTURE_DIR = "./pictures/coin.png";
    std::vector<Item> coins;
    sf::Texture diomondTexture;
    const std::string DIOMOND_TEXTURE_DIR = "./pictures/diomond.png";
    std::vector<Item> diomonds;
    sf::Texture enemyTexture;
    const std::string ENEMY_TEXTURE_DIR = "./pictures/enemy.png";
    sf::Texture wildEnemyTexture;
    const std::string WILD_ENEMY_TEXTURE_DIR = "./pictures/wild-enemy.png";
    std::vector<Enemy> enemies;
    sf::Texture portalTexture;
    const std::string PORTAL_TEXTURE_DIR = "./pictures/portal.png";
    Portal* portal;
    sf::Texture bubbleBabyTexture;
    const std::string BUBBLE_BABY_TEXTURE_DIR = "./pictures/bubble-baby.png";
    sf::Texture babyTexture;
    const std::string BABY_TEXTURE_DIR = "./pictures/baby.png";
    std::vector<Baby> babies;
    sf::Texture tiqTexture;
    const std::string TIQ_TEXTURE_DIR = "./pictures/tiq.png";
    std::vector<Tiq> tiqs;
    const int TILE_SIZE = 64;

    sf::Font font;
    std::string FONT_DIR = "./fonts/kenvector_future.ttf";

};

#endif /* MAP_HPP */