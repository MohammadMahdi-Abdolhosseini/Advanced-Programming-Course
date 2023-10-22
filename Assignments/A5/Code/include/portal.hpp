#ifndef PORTAL_HPP
#define PORTAL_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Portal {
public:
    Portal(sf::Texture &texture, sf::Vector2f position);

    void draw(sf::RenderWindow& window) const;

    sf::FloatRect getBounds();
    sf::Sprite& getSprite();

private:
    sf::Sprite sprite;
};

#endif /* PORTAL_HPP */