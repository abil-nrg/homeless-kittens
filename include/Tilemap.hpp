#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.hpp"

class Tilemap
{
    public:
        Tilemap(int WIDTH, int HEIGHT, int TILE_SIZE);

        void draw(sf::RenderWindow &window);
        bool getTileFromPixel(int pixelX, int pixelY, int &tileX, int &tileY);
        void toggleTile(int x, int y);

    private:
        int WIDTH;
        int HEIGHT;
        int TILE_SIZE;
    
        std::vector<std::vector<Tile>> grid;
};