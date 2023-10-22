#include "../include/tiq.hpp"
using namespace std;

Tiq::Tiq(sf::Texture &texture, sf::Vector2f position){
    m_sprite.setTexture(texture);
    m_sprite.setPosition(position);
}

void Tiq::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}

sf::FloatRect Tiq::getBounds() {
    return m_sprite.getGlobalBounds();
}