#ifndef ITEM_HPP
#define ITEM_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

const int COIN_SCORE = 10;
const int DIOMOND_SCORE = 50;

class Item {
public:
    Item(sf::Texture &texture, sf::Vector2f position, int score);

    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds();
    int getScore();

private:
    int m_score;
    sf::Sprite sprite;
};

#endif // ITEM_HPP
