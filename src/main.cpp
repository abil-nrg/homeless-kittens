#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.hpp"

int main(){
    int width = 25;
    int height = 25;
    int tile_size = 30;
    Game game(width, height, tile_size);
    game.run();
    return 0;
}