#include "Tilemap.hpp"
#include <stdexcept>

Tilemap::Tilemap(int WIDTH, int HEIGHT, int TILE_SIZE)
:   WIDTH(WIDTH),
    HEIGHT(HEIGHT),
    TILE_SIZE(TILE_SIZE){
    grid.resize(HEIGHT, std::vector<Tile>(WIDTH));

    for(int y = 0; y < HEIGHT; y ++){
        for(int x = 0; x < WIDTH; x++){
            if(x == 0 | y == 0 | x == HEIGHT - 1 | y == WIDTH - 1){
                grid[y][x] = Tile(false, sf::Color::Red);
            }
            else{
                grid[y][x] = Tile(true, sf::Color::Green);
            }
        }
    }
}

void Tilemap::draw(sf::RenderWindow& window){
    sf::RectangleShape rect;
    rect.setSize({TILE_SIZE, TILE_SIZE});

    for(int y = 0; y < HEIGHT; y ++ ){
        for(int x = 0; x < WIDTH; x++){
            rect.setFillColor(grid[y][x].getColor());
            rect.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            window.draw(rect);
        }
    }
}

bool Tilemap::getTileFromPixel(int pixelX, int pixelY, int &tileX, int &tileY){
    if(pixelX < 0 || pixelY < 0){
        return false;
    }

    tileX = pixelX / TILE_SIZE;
    tileY = pixelY / TILE_SIZE;
    return true;
}

void Tilemap::toggleTile(int x, int y){
    if(x < 0 || y < 0 || (x > WIDTH - 1) || (y > HEIGHT - 1)){
        throw std::invalid_argument("Tile Out of Bounds");
    }

    Tile &tile = grid[y][x];

    if(tile.isWalkable()){
        tile = Tile(false, sf::Color::Red);
    }
    else{
        tile = Tile(true, sf::Color::Green);
    }
}