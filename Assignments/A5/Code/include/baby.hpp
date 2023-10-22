#ifndef BABY_HPP
#define BABY_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/platform.hpp"

class Baby {
public:
    Baby(sf::Texture &texture, sf::Vector2f position, sf::Texture &textureB);
    void update(float deltaTime, std::vector<Platform>& platform);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds();
    bool getOutOfBubble();
    void setOutOfBubble(bool outOfBubble);
    void toggleCanJump();
    void updateTexture();

private:
    bool m_outOfBubble = false;
    sf::Sprite m_sprite;
    float m_speed = 10;
    bool m_canJump = false;
    float m_jumpSpeed = 70;
    float m_gravity = 9.8;
    sf::Vector2f m_velocity{0, 0};
    sf::Vector2f m_newPosition;
    bool m_movingLeft = false;
    bool m_jumping = false;

    bool collisionWithTop = false;
    bool collisionWithRight = false;
    bool collisionWithLeft = false;
    bool collisionWithBottom = false;

    void platformsCollisionHandler (std::vector<Platform>& platforms);

    sf::Texture babyTexture;
};

#endif // BABY_HPP
