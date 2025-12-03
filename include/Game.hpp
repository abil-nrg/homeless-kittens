#pragma once
#include <SFML/Graphics.hpp>
#include "Tilemap.hpp" 

class Game
{
    public:
        Game(int gridWidth, int gridHeight, int tileSize);
        void run();
    private:
        void processEvent();
        void update();
        void render();

        int width;
        int height;
        sf::RenderWindow window;
        Tilemap* tilemap;
};
