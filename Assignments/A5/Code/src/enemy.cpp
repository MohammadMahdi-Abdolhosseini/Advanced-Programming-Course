#include "../include/enemy.hpp"
using namespace std;

Enemy::Enemy(sf::Texture &texture, sf::Vector2f position, int type){
    m_sprite.setTexture(texture);
    m_sprite.setPosition(position);
    m_type = type;
}

void Enemy::update(float deltaTime, vector<Platform>& platforms)
{
    if (m_movingLeft) m_velocity.x = -m_speed;
    else m_velocity.x = m_speed;

    m_newPosition = m_sprite.getPosition() + (m_velocity * deltaTime);
    platformsCollisionHandler(platforms);

    if (collisionWithRight || collisionWithLeft)
        m_movingLeft = !m_movingLeft;
    if (collisionWithTop || collisionWithBottom)
        m_velocity.y = 0;
    
    m_sprite.move(m_velocity * deltaTime);
    m_velocity.y += m_gravity * deltaTime;

    if (m_type == 2 && !m_jumping){
        m_velocity.y = -m_jumpSpeed;
        m_jumping = !m_jumping;
    }

}

void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}

sf::FloatRect Enemy::getBounds() {
    return m_sprite.getGlobalBounds();
}

int Enemy::getType() {
    return m_type;
}

void Enemy::platformsCollisionHandler (vector<Platform>& platforms) {
    collisionWithTop = false;
    collisionWithRight = false;
    collisionWithLeft = false;
    collisionWithBottom = false;
    for (auto& platform : platforms) {
        if (sf::FloatRect(m_newPosition.x, m_sprite.getPosition().y, m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height).intersects(platform.getBounds())) {
            float enemyLeft = m_newPosition.x;
            float enemyRight = m_newPosition.x + m_sprite.getGlobalBounds().width;
            float platformLeft = platform.getBounds().left;
            float platformRight = platform.getBounds().left + platform.getBounds().width;
            if (enemyRight > platformLeft && m_velocity.x < 0) collisionWithLeft = true;
            else if (enemyLeft < platformRight && m_velocity.x > 0) collisionWithRight = true;
        }
        if (sf::FloatRect(m_sprite.getPosition().x, m_newPosition.y, m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height).intersects(platform.getBounds())) {
            float enemyTop = m_newPosition.y;
            float enemyBottom = m_newPosition.y + m_sprite.getGlobalBounds().height;
            float platformTop = platform.getBounds().top;
            float platformBottom = platform.getBounds().top + platform.getBounds().height;
            if (enemyBottom > platformTop && m_velocity.y > 0) {
                collisionWithBottom = true;
                m_jumping = false;
            }
            else if (enemyTop < platformBottom && m_velocity.y < 0) collisionWithTop = true;
        }
    }
}