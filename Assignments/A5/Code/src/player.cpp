#include "../include/player.hpp"

using namespace std;

Player::Player(float x, float y){

    if (!texture.loadFromFile(H3_TEXTURE_DIR))
        cerr << "CANT LOAD " << H3_TEXTURE_DIR << endl;
    origPosX = x;
    origPosY = y;
    m_sprite.setTexture(texture);
    m_sprite.setPosition(x,y);

}

void Player::update(float deltaTime, Map& map)
{
    if (m_movingLeft)
        m_velocity.x = -m_speed;
    else if (m_movingRight)
        m_velocity.x = m_speed;
    else m_velocity.x = 0;

    m_newPosition = m_sprite.getPosition() + (m_velocity * deltaTime);
    platformsCollisionHandler(map.getPlatforms());

    itemsCollisionHandler(map.getCoins());
    itemsCollisionHandler(map.getDiomonds());

    if (collisionWithRight || collisionWithLeft)
        m_velocity.x = 0;
    if (collisionWithTop || collisionWithBottom)
        m_velocity.y = 0;

    if (m_health > 0){
        m_sprite.move(m_velocity * deltaTime);
        m_velocity.y += m_gravity * deltaTime;
    }

    enemiesCollisionHandler(map.getEnemies());
    babiesCollisionHandler(map.getBabies());
    tiqsCollisionHandler(map.getTiqs());
    gameOverHandler(map);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

void Player::setMovingLeft(bool movingLeft)
{
    m_movingLeft = movingLeft;
}

void Player::setMovingRight(bool movingRight)
{
    m_movingRight = movingRight;
}

void Player::jump()
{
    if (!m_jumping)
    {
        m_velocity.y = -m_jumpSpeed;
        m_jumping = true;
    }
}

void Player::reset(){
    m_sprite.setPosition(origPosX,origPosY);
    m_velocity.x = 0;
    m_velocity.y = 0;
}

void Player::setOrigPos(sf::Vector2f spawnPoint){
    origPosX = spawnPoint.x;
    origPosY = spawnPoint.y;
}

void Player::setWinState(int state){
    m_winState = state;
}

void Player::setScore(int score){
    m_score = score;
}

sf::Sprite& Player::getSprite()
{
    return m_sprite;
}

int Player::getScore(){
    return m_score;
}

int Player::getWinState(){
    return m_winState;
}

void Player::gotHurt(){
    if(godMode) return;
    m_health--;
    updateHealthTexture();
}

void Player::updateHealthTexture(){
    if(m_health == 2){
        if (!texture.loadFromFile(H2_TEXTURE_DIR))
            cerr << "CANT LOAD " << H2_TEXTURE_DIR << endl;
        m_sprite.setTexture(texture);
        reset();
    }
    else if(m_health == 1){
        if (!texture.loadFromFile(H1_TEXTURE_DIR))
            cerr << "CANT LOAD " << H1_TEXTURE_DIR << endl;
        m_sprite.setTexture(texture);
        reset();
    }
    else if(m_health == 0){
        if (!texture.loadFromFile(H0_TEXTURE_DIR))
            cerr << "CANT LOAD " << H0_TEXTURE_DIR << endl;
        m_sprite.setTexture(texture);
        reset();
    }
}

void Player::platformsCollisionHandler (vector<Platform>& platforms) {
    collisionWithTop = false;
    collisionWithRight = false;
    collisionWithLeft = false;
    collisionWithBottom = false;  
    for (auto& platform : platforms) {
        if (sf::FloatRect(m_newPosition.x, m_sprite.getPosition().y, m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height).intersects(platform.getBounds())) {
            float playerLeft = m_newPosition.x;
            float playerRight = m_newPosition.x + m_sprite.getGlobalBounds().width;
            float platformLeft = platform.getBounds().left;
            float platformRight = platform.getBounds().left + platform.getBounds().width;
            if (playerRight > platformLeft && m_velocity.x < 0) collisionWithLeft = true;
            else if (playerLeft < platformRight && m_velocity.x > 0) collisionWithRight = true;
        }
        if (sf::FloatRect(m_sprite.getPosition().x, m_newPosition.y, m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height).intersects(platform.getBounds())) {
            float playerTop = m_newPosition.y;
            float playerBottom = m_newPosition.y + m_sprite.getGlobalBounds().height;
            float platformTop = platform.getBounds().top;
            float platformBottom = platform.getBounds().top + platform.getBounds().height;
            if (playerBottom > platformTop && m_velocity.y > 0) {
                collisionWithBottom = true;
                m_jumping = false;
            }
            else if (playerTop < platformBottom && m_velocity.y < 0) collisionWithTop = true;
        }
    }
}

void Player::itemsCollisionHandler(std::vector<Item>& items) {
    for (auto it = items.begin(); it != items.end(); it++) {
        if (m_sprite.getGlobalBounds().intersects((*it).getBounds())) {
            m_score += (*it).getScore();
            items.erase(it);
            break;
        }
    }
}

void Player::enemiesCollisionHandler (vector<Enemy>& enemies) {
    for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++) {
        if (m_sprite.getGlobalBounds().intersects((*enemy).getBounds())) {
            float playerBottom = m_sprite.getPosition().y + m_sprite.getGlobalBounds().height;
            float enemyTop = (*enemy).getBounds().top;
            if (playerBottom > enemyTop && m_velocity.y > 1){
                m_velocity.y = -0.75f*m_velocity.y;
                enemies.erase(enemy);
                m_score += COIN_SCORE*enemy->getType();
                break;
            }
            else gotHurt();
        }
    }
}

void Player::tiqsCollisionHandler (vector<Tiq>& tiqs) {
    for (auto tiq = tiqs.begin(); tiq != tiqs.end(); tiq++) {
        if (m_sprite.getGlobalBounds().intersects((*tiq).getBounds())) {
            gotHurt();
        }
    }
}

void Player::gameOverHandler(Map& map){
    if (m_sprite.getGlobalBounds().intersects((map.getPortal()).getBounds())) {
        //if(!(map.getCoins().size() || map.getDiomonds().size() || map.getEnemies().size() || map.getBabies().size())){
        if(!map.getBabies().size()){
            m_winState = 1;
            m_score += DIOMOND_SCORE;
        }
        else if(m_health < 1){
            m_winState = -1;
        }
    }
}

void Player::babiesCollisionHandler (vector<Baby>& babies) {
    for (auto baby = babies.begin(); baby != babies.end(); baby++) {
        if (m_sprite.getGlobalBounds().intersects((*baby).getBounds())) {
            if(!(*baby).getOutOfBubble()){
                m_score += COIN_SCORE;
            }
            (*baby).setOutOfBubble(true);
            (*baby).updateTexture();
        }
    }
}

void Player::toggleGodMode(){
    if(firstTime){
        cout << "You cheated not only the game, but yourself." << endl << endl;
        cout << "You didn't grow." << endl;
        cout << "You didn't improve." << endl;
        cout << "You took a shortcut and gained nothing." << endl << endl;
        cout << "You experienced a hollow victory." << endl;
        cout << "Nothing was risked and nothing was gained." << endl << endl;
        cout << "It's sad that you don't know the difference." << endl << endl;
    }
    godMode = !godMode;
    firstTime = false;
    if(godMode)
        cout << "God Mode is On" << endl;
    else
        cout << "God Mode is Off" << endl;
}
