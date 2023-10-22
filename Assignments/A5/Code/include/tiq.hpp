#ifndef TIQ_HPP
#define TIQ_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Tiq {
public:
    Tiq(sf::Texture &texture, sf::Vector2f position);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds();

private:
    sf::Sprite m_sprite;
};

#endif // TIQ_HPP
