#include "../include/baby.hpp"
using namespace std;

Baby::Baby(sf::Texture &texture, sf::Vector2f position, sf::Texture &textureB){
    m_sprite.setTexture(texture);
    m_sprite.setPosition(position);
    babyTexture = textureB;
}

void Baby::update(float deltaTime, std::vector<Platform>& platforms)
{
    if (!m_outOfBubble) return;
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

    if (m_canJump && !m_jumping){
        m_velocity.y = -m_jumpSpeed;
        m_jumping = !m_jumping;
    }

}

void Baby::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}

sf::FloatRect Baby::getBounds() {
    return m_sprite.getGlobalBounds();
}

bool Baby::getOutOfBubble(){
    return m_outOfBubble;
}

void Baby::setOutOfBubble(bool outOfBubble){
    m_outOfBubble = outOfBubble;
}

void Baby::toggleCanJump(){
    m_canJump = !m_canJump;
}

void Baby::updateTexture(){
    m_sprite.setTexture(babyTexture);
}

void Baby::platformsCollisionHandler (vector<Platform>& platforms) {
    collisionWithTop = false;
    collisionWithRight = false;
    collisionWithLeft = false;
    collisionWithBottom = false;
    for (auto& platform : platforms) {
        if (sf::FloatRect(m_newPosition.x, m_sprite.getPosition().y, m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height).intersects(platform.getBounds())) {
            float babyLeft = m_newPosition.x;
            float babyRight = m_newPosition.x + m_sprite.getGlobalBounds().width;
            float platformLeft = platform.getBounds().left;
            float platformRight = platform.getBounds().left + platform.getBounds().width;
            if (babyRight > platformLeft && m_velocity.x < 0) collisionWithLeft = true;
            else if (babyLeft < platformRight && m_velocity.x > 0) collisionWithRight = true;
        }
        if (sf::FloatRect(m_sprite.getPosition().x, m_newPosition.y, m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height).intersects(platform.getBounds())) {
            float babyTop = m_newPosition.y;
            float babyBottom = m_newPosition.y + m_sprite.getGlobalBounds().height;
            float platformTop = platform.getBounds().top;
            float platformBottom = platform.getBounds().top + platform.getBounds().height;
            if (babyBottom > platformTop && m_velocity.y > 0) {
                collisionWithBottom = true;
                m_jumping = false;
            }
            else if (babyTop < platformBottom && m_velocity.y < 0) collisionWithTop = true;
        }
    }
}