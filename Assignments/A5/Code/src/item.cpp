#include "../include/item.hpp"
using namespace std;

Item::Item(sf::Texture &texture, sf::Vector2f position, int score){
    sprite.setTexture(texture);
    sprite.setPosition(position);
    m_score = score;
}

void Item::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect Item::getBounds() {
    return sprite.getGlobalBounds();
}

int Item::getScore() {
    return m_score;
}