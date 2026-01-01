#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.hpp"

class Tilemap
{
    public:
        Tilemap(int WIDTH, int HEIGHT, int TILE_SIZE, float ORI_X, float ORI_Y);

        void draw(sf::RenderWindow &window);
        bool getTileFromPixel(int pixelX, int pixelY, int &tileX, int &tileY);
        void toggleTile(int x, int y);
        void updateDirField();
        void moveKitty(std::vector<std::vector<Tile>> &grid_next, int &inc);
        void createKitty(std::vector<std::vector<Tile>> &grid_next);
        Tile& getAdjTile(int x, int y, int dir, std::vector<std::vector<Tile>> &mat);
        int pathFinder(int x, int y, int prev_x, int prev_y);
        int update(int score);

    private:
        int WIDTH;
        int HEIGHT;
        int TILE_SIZE;
        float ORI_X; //where to place the grid
        float ORI_Y;
    
        std::vector<std::vector<Tile>> grid; // holds tiles
        std::vector<std::vector<int>> dir_field; // holds direction of kitty

};