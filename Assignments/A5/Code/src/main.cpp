#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "../include/game.hpp"

using namespace std;

int main()
{
    Game game;
    
    while(game.getWindow().isOpen()){
        game.update();
        game.render();
    }
    
    return 0;
}