#include "Game.hpp"
#include <iostream>

Game::Game(int gridWidth, int gridHeight, int tileSize, float ori_x, float ori_y) 
:   width(gridWidth * tileSize + 2 * ori_x),
    height(gridHeight * tileSize + 2 * ori_y),
    window(sf::VideoMode({width, height}), "Homeless Kittens"){
    window.setVerticalSyncEnabled(true); // set freq same as monitor refresh rate

    tilemap = new Tilemap(gridWidth, gridHeight, tileSize, ori_x, ori_y);
}

void Game::run(){
    while(window.isOpen()){
        processEvent();
        update();
        render();
    }
}

void Game::processEvent(){
    sf::Event event;
    while(window.pollEvent(event)){
        static bool lock_click;
        if(event.type == sf::Event::Closed)
            window.close();
        
        if(event.type == sf::Event::MouseButtonPressed){
            if(event.mouseButton.button == sf::Mouse::Left && lock_click != true){
                int pixelX = event.mouseButton.x;
                int pixelY = event.mouseButton.y;

                int tileX, tileY;
                
                if(tilemap->getTileFromPixel(pixelX, pixelY, tileX, tileY)){
                   tilemap->toggleTile(tileX, tileY);
                }
            }
        }
        if(event.type == sf::Event::MouseButtonReleased){
            if(event.type == sf::Event::MouseLeft && lock_click == true){
                lock_click = false;
            }
        }

        if(event.type = sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Enter){
                tilemap->update();
            }
        }
    }
}

void Game::update(){
    //amazing game logic goes here
}

void Game::render(){
    window.clear();
    tilemap->draw(window);
    window.display();
}