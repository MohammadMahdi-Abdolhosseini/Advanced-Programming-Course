#include "../include/portal.hpp"

using namespace std;

Portal::Portal(sf::Texture &texture, sf::Vector2f position){

    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void Portal::draw(sf::RenderWindow& window) const
{
    window.draw(sprite);
}

sf::FloatRect Portal::getBounds()
{
    return sprite.getGlobalBounds();
}

sf::Sprite& Portal::getSprite()
{
    return sprite;
}