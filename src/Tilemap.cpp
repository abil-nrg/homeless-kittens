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
            /*if(x == 0 | y == 0 | x == HEIGHT - 1 | y == WIDTH - 1){
                grid[y][x] = Tile(0, sf::Color::Red);
            }
            else{
                grid[y][x] = Tile(1, sf::Color::Green);
            }*/
           grid[y][x] = Tile(1, sf::Color::Green);
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
            //find a factory, run thru it
            if(tile.getKind() == FACTORY){
                std::cout << "FOUND FACTORY AT (" << x << "," << y <<")\n";
                if(!pathFinder(x,y, -1, -1))
                    std::cout << "Failed to find path\n";
            }

            else if(!dir){ //make sure we are not overwriting
                dir = 0;
            }
        }
    }
}

void Tilemap::createKitty(std::vector<std::vector<Tile>> &grid_next){
    /*
    Handles the creation of kittys from factorys
    at appropriate time
    */
}

void Tilemap::moveKitty(std::vector<std::vector<Tile>> &grid_next, int &inc){
    /*
    Moves existing kitties
    */
    
    for(int y =0; y < HEIGHT; y ++){
        for(int x = 0; x < WIDTH; x++){
            Tile &tile = grid[y][x];
            int dir = dir_field[y][x];
            Tile &tile_next = getAdjTile(x , y, dir, grid);

            if(tile.getKind() == KITTY){
                std::cout << "FOUND KITTY AT (" << x << "," << y << ")\n";
                grid_next[y][x] = Tile(TRACK, sf::Color::Black);

                if(tile_next.getKind() == TRACK || tile_next.getKind() == KITTY){
                    getAdjTile(x, y, dir, grid_next) = Tile(KITTY, sf::Color::Cyan);
                }

                if(tile_next.getKind() == HOUSE){
                    inc++;
                }
            }
        }
    }
    
}

Tile &Tilemap::getAdjTile(int x, int y, int dir, std::vector<std::vector<Tile>> &mat){
    /*
    Returns the tile DIR of the tile
    */

    if(dir == NORTH)
        y --;
    else if(dir == SOUTH)
        y ++;
    else if(dir == WEST)
        x --;
    else if(dir == EAST)
        x ++;

    return mat[y][x];
}

int Tilemap :: pathFinder(int x, int y, int prev_x, int prev_y){
    /*
    Given your current location, recursevly 
    fill in the rest of the path to the house
    */
    Tile &tile = grid[y][x];
    int &dir = dir_field[y][x];

    std::cout << "at tile (" << x << "," << y << ") -- is " << tile.getKind() << " == marked as going ";

    int tile_kind = tile.getKind();

    if(tile_kind == HOUSE){ //we are done
        std::cout << "HOUSE \n";
        dir = 0;
        return 1;
    }
    else if(tile_kind == TRACK || tile_kind == KITTY){
        // always point toward non-prev neighbour
        
        if(grid[y][x + 1].getKind() != GRASS && ((y != prev_y) || (x + 1 != prev_x))){
            dir = EAST;
            std::cout << "EAST\n";
            return pathFinder(x + 1, y, x, y);
        }
        else if(grid[y][x-1].getKind() != GRASS && ((y != prev_y) || (x - 1 != prev_x))){
            dir = WEST;
            std::cout << "WEST\n";
            return pathFinder(x -1, y, x, y);
        }
        else if(grid[y - 1][x].getKind() != GRASS && ((y  - 1 != prev_y) || (x != prev_x))){
            dir = NORTH;
            std::cout << "NORTH\n";
            return pathFinder(x, y - 1, x, y);
        }
        else if(grid[y + 1][x].getKind() != GRASS && ((y + 1 != prev_y) || (x != prev_x))){
            dir = SOUTH;
            std::cout << "SOUTH\n";
            return pathFinder(x, y + 1, x, y);
        }

    }
    else if(tile.getKind() == FACTORY){
        //TODO ALLOW KITTENS NEAR THE FACTORY
        std::cout << "factory \n";
        //look for neighbouring track, Prio in the below order
        if(grid[y][x + 1].getKind() != GRASS){
            dir = EAST;
            return pathFinder(x + 1, y, x, y);
        }
        else if(grid[y][x-1].getKind() != GRASS){
            dir = WEST;
            return pathFinder(x - 1, y, x, y);
        }
        else if(grid[y - 1][x].getKind() != GRASS){
            dir = NORTH;
            return pathFinder(x, y - 1, x, y);

        }
        else if(grid[y + 1][x].getKind() != GRASS){
            dir = SOUTH;
            return pathFinder(x, y + 1, x, y);

        }
    }

    std::cout << "pathFinder Broke on tile (" << x << "," << y << ")\n";
    return 0;
    
}

int Tilemap::update(int score){

    //Yes, I loop over grid in each function, even tho 
    //I could do it once. I thought its more important
    //to keep this readable. My CPU strong enough!

    std::vector<std::vector<Tile>> grid_next = grid;
    int inc=0;
    updateDirField();
    moveKitty(grid_next, inc);
    createKitty(grid_next);
    grid = grid_next;
    
    std::cout << "DIRECTION FIELD\n";
    for(int i = 0; i < HEIGHT; i ++){
        for(int j = 0; j < WIDTH; j++){
            std::cout << dir_field[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "==============\n";

    return score + inc;
}

