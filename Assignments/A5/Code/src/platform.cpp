#include "../include/platform.hpp"

using namespace std;

Platform::Platform(sf::Texture &texture, sf::Vector2f position){

    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void Platform::update()
{
    // there's nothing to update for a platform
}

void Platform::draw(sf::RenderWindow& window) const
{
    window.draw(sprite);
}

sf::FloatRect Platform::getBounds()
{
    return sprite.getGlobalBounds();
}