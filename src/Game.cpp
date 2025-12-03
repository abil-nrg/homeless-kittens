#include "Game.hpp"
#include <iostream>

Game::Game(int gridWidth, int gridHeight, int tileSize) 
:   width(gridWidth * tileSize),
    height(gridHeight * tileSize),
    window(sf::VideoMode({width, height}), "Homeless Kittens"){
    window.setVerticalSyncEnabled(true); // set freq same as monitor refresh rate

    tilemap = new Tilemap(gridWidth, gridHeight, tileSize);
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