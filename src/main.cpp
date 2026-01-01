#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.hpp"

int main(){
    int width = 30;
    int height = 30;
    int tile_size = 25;
    float ori_x = 100.0f;
    float ori_y = 100.0f;
    Game game(width, height, tile_size, ori_x, ori_y);
    game.run();
    return 0;
}