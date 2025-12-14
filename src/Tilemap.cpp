#include "Tilemap.hpp"
#include <iostream>

#define WALL 0
#define GRASS 1
#define TRACK 2
#define KITTY 3
#define HOUSE 4
#define FACTORY 5

#define NORTH 1
#define EAST 2
#define SOUTH 3
#define WEST 4

Tilemap::Tilemap(int WIDTH, int HEIGHT, int TILE_SIZE, float ORI_X, float ORI_Y)
:   WIDTH(WIDTH),
    HEIGHT(HEIGHT),
    TILE_SIZE(TILE_SIZE),
    ORI_X(ORI_X),
    ORI_Y(ORI_Y){
    grid.resize(HEIGHT, std::vector<Tile>(WIDTH));
    dir_field.resize(HEIGHT, std::vector<int>(WIDTH));

    for(int y = 0; y < HEIGHT; y ++){ //paint the outside
        for(int x = 0; x < WIDTH; x++){
            if(x == 0 | y == 0 | x == HEIGHT - 1 | y == WIDTH - 1){
                grid[y][x] = Tile(0, sf::Color::Red);
            }
            else{
                grid[y][x] = Tile(1, sf::Color::Green);
            }
        }
    }

    updateDirField();
}

void Tilemap::draw(sf::RenderWindow& window){
    sf::RectangleShape rect;
    rect.setSize({TILE_SIZE, TILE_SIZE});

    for(int y = 0; y < HEIGHT; y ++ ){
        for(int x = 0; x < WIDTH; x++){
            rect.setFillColor(grid[y][x].getColor());
            rect.setPosition(x * TILE_SIZE + ORI_X, y * TILE_SIZE + ORI_Y);
            window.draw(rect);
        }
    }
}

bool Tilemap::getTileFromPixel(int pixelX, int pixelY, int &tileX, int &tileY){
    if(pixelX < 0 || pixelY < 0){
        return false;
    }

    tileX = (pixelX - ORI_X) / TILE_SIZE;
    tileY = (pixelY - ORI_Y) / TILE_SIZE;
    return true;
}

void Tilemap::toggleTile(int x, int y){
    if(x < 0 || y < 0 || (x > WIDTH - 1) || (y > HEIGHT - 1)){
        std::cout << "Player is out of bounds\n";
        return;
    }

    Tile &tile = grid[y][x];

    //i know this is trash, just want to see it working
    if(tile.getKind() == WALL){
        tile = Tile(GRASS, sf::Color::Green); //empty space
    }
    else if(tile.getKind() == GRASS){
        tile = Tile(TRACK, sf::Color::Black); // track
    }
    else if(tile.getKind() == TRACK){
        tile = Tile(KITTY, sf::Color::Cyan); // 
    }
    else if(tile.getKind() == KITTY){
        tile = Tile(HOUSE, sf::Color::White); // 
    }
    else if(tile.getKind() == HOUSE){
        tile = Tile(FACTORY, sf::Color::Magenta); // 
    }
    else{
        tile = Tile(0, sf::Color::Red);
    }
}

void Tilemap::updateDirField(){
    /*
    Based off of the grid, at each point write the 
    direction of movement
    */
    
    //for now only works WITHOUT switches / forks

    for(int y = 0; y < HEIGHT; y ++){
        for(int x = 0; x < WIDTH; x ++){
            Tile &tile = grid[y][x];
            int &dir = dir_field[y][x];

            if(tile.getKind() == FACTORY){ //source
                if(!pathFinder(x,y, -1, -1))
                    std::cout << "Failed to find path\n";
            }

            else if(tile.getKind() != HOUSE && tile.getKind() == TRACK){
                dir = 0;
            }
        }
    }
}

int Tilemap :: pathFinder(int x, int y, int prev_x, int prev_y){
    /*
    Given your current location, recursevly 
    fill in the rest of the path to the house
    */
    Tile &tile = grid[y][x];
    int &dir = dir_field[y][x];

    if(tile.getKind() == HOUSE){ //we are done
        dir = 0;
        return 1;
    }
    else if(tile.getKind() == TRACK){
        // behavior depends on the combo of adjacencies
        // factory + X : towards X
        // X + house : towards house
        // track + track : towards the track that isnt prev location
    }
    else if(tile.getKind() == FACTORY){
        //look for neighbouring track, Prio in the below order
        if(grid[y][x + 1].getKind() == TRACK)
            dir = SOUTH;
        else if(grid[y][x-1].getKind() == TRACK)
            dir = NORTH;
        else if(grid[y + 1][x].getKind() == TRACK)
            dir = WEST;
        else if(grid[y - 1][x].getKind() == TRACK)
            dir = EAST;
    }
    
}

void Tilemap::update(){

    updateDirField();
    //find all kittys + create if need be
    //move them in the correct direction
    //make sure they are legal moves
}