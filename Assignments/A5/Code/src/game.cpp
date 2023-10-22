#include "../include/game.hpp"

using namespace std;

Game::Game(){
    this->initWindow();
    this->map = new Map();   
    this->map->loadMap(LEVEL1);
    sf::Vector2f spawnPoint = map->getPortal().getSprite().getPosition();
    this->player = new Player(spawnPoint.x, spawnPoint.y);
    
}

void Game::initWindow(){
    this->window.create(sf::VideoMode(TILE_SIZE * MAP_WIDTH,TILE_SIZE * MAP_HEIGHT),"chadGame", sf::Style::Close| sf::Style::Titlebar);
    view.setCenter(player->getSprite().getPosition());
    view.setSize(sf::Vector2f(MAP_WIDTH*60, MAP_HEIGHT*60));
    window.setView(view);
}

const sf::RenderWindow& Game::getWindow() const {
    return this->window;
}

void Game::update(){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::A)
                    player->setMovingLeft(true);
                else if (event.key.code == sf::Keyboard::D)
                    player->setMovingRight(true);
                else if (event.key.code == sf::Keyboard::R)
                    player->reset();
                else if (event.key.code == sf::Keyboard::Q)
                    for(auto& baby : map->getBabies())
                        baby.toggleCanJump();
                else if (event.key.code == sf::Keyboard::G)
                    player->toggleGodMode();
                else if (event.key.code == sf::Keyboard::E){
                    sf::Vector2f position = player->getSprite().getPosition();
                    position.y += TILE_SIZE;
                    map->addPlatformAtPosition(position);
                }
                else if (event.key.code == sf::Keyboard::W)
                    player->jump();
                else if (event.key.code == sf::Keyboard::H){
                    player->gotHurt();
                }
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::A)
                    player->setMovingLeft(false);
                else if (event.key.code == sf::Keyboard::D)
                    player->setMovingRight(false);
            }
        }

    player->update(0.015f, *map);
    for (auto& enemy : map->getEnemies())
    {
        enemy.update(0.015f, map->getPlatforms());
    }
    for (auto& baby : map->getBabies())
    {
        baby.update(0.015f, map->getPlatforms());
    }
    babyCollisionWithPortalHandler();
    gameOverCheck();
    
}


void Game::render(){
    window.clear();
    map->draw(window);
    view.setCenter(player->getSprite().getPosition());
    window.setView(view);
    player->draw(window);
    drawScore(player->getScore());
    drawRemainingBaby(map->getBabies().size());
    drawLevel(currLevel+1);
    window.display();  
}

void Game::drawScore(int score){
    sf::Text scoreText("Score: " + std::to_string(score), map->getFont(), 25);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(player->getSprite().getPosition().x + 400, player->getSprite().getPosition().y - 280);
    window.draw(scoreText);
}

void Game::drawRemainingBaby(int remainingBaby){
    sf::Text remainingBabyText("Remaining Baby(s): " + std::to_string(remainingBaby), map->getFont(), 15);
    remainingBabyText.setFillColor(sf::Color::Green);
    remainingBabyText.setPosition(player->getSprite().getPosition().x + 380, player->getSprite().getPosition().y - 240);
    window.draw(remainingBabyText);
}

void Game::drawLevel(int lvl){
    sf::Text lvlText("Level: " + std::to_string(lvl), map->getFont(), 30);
    lvlText.setFillColor(sf::Color::Cyan);
    lvlText.setPosition(player->getSprite().getPosition().x - 550, player->getSprite().getPosition().y - 280);
    window.draw(lvlText);
    if (lvl == 10){
        sf::Text lvlText2("Congratulations!\nYou have achieved\nthe ultimate goal\nof this video game.\n\n\nNow go outside and\nget some fresh air,\nyou've earned it!", map->getFont(), 50);
        lvlText2.setFillColor(sf::Color::Yellow);
        lvlText2.setPosition(player->getSprite().getPosition().x - 300, player->getSprite().getPosition().y - 250);
        window.draw(lvlText2);
    }
}

void Game::loadLevel(){
    switch (currLevel)
        {
        case 0:
            this->map->loadMap(LEVEL1);
            break;
        case 1:
            this->map->loadMap(LEVEL2);
            break;
        case 2:
            this->map->loadMap(LEVEL3);
            break;
        case 3:
            this->map->loadMap(LEVEL4);
            break;
        case 4:
            this->map->loadMap(LEVEL5);
            break;
        case 5:
            this->map->loadMap(LEVEL6);
            break;
        case 6:
            this->map->loadMap(LEVEL7);
            break;
        case 7:
            this->map->loadMap(LEVEL8);
            break;
        case 8:
            this->map->loadMap(LEVEL9);
            break;
        case 9:
            this->map->loadMap(LEVEL11);
            break;
        case 10:
            window.close();
            break;
        default:
            break;
        }
}

void Game::gameOverCheck(){
    if (player->getWinState() == 1){
        currLevel ++;
        //this->map->loadMap(map->getLevels()[map->getCurrentLevel]);
        loadLevel();       
        player->setOrigPos(map->getPortal().getSprite().getPosition());
        player->setWinState(0);
        player->reset();
        //map->setCurrentLevel(map->getCurrentLevel()+1);
    }
    
}

void Game::babyCollisionWithPortalHandler(){
    for (auto baby = this->map->getBabies().begin(); baby != this->map->getBabies().end(); baby++) {
        if (this->map->getPortal().getSprite().getGlobalBounds().intersects((*baby).getBounds())) {
            this->map->getBabies().erase(baby);
            this->player->setScore(this->player->getScore() + DIOMOND_SCORE);
            break;
        }
    }
}

