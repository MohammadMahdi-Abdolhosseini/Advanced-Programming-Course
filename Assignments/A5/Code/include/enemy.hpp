#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/platform.hpp"

class Enemy {
public:
    Enemy(sf::Texture &texture, sf::Vector2f position, int type);
    void update(float deltaTime, std::vector<Platform>& platforms);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds();
    int getType();

private:
    int m_type;
    sf::Sprite m_sprite;
    float m_speed = 10;
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
};

#endif // ENEMY_HPP
