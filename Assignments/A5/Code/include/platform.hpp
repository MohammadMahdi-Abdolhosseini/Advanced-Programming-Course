#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Platform {
public:
    Platform(sf::Texture &texture, sf::Vector2f position);

    void update();
    void draw(sf::RenderWindow& window) const;

    sf::FloatRect getBounds();

private:
    sf::Sprite sprite;
};

#endif /* PLATFORM_HPP */