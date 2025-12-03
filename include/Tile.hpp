#pragma once
#include <SFML/Graphics.hpp>

class Tile
{
    public:
        Tile(bool walkable = true, sf::Color color = sf::Color::White)
            : walkable(walkable), color(color) {}
        
        bool isWalkable() const {return walkable; }
        
        const sf::Color& getColor() const {return color; }

    private:
        bool walkable;
        sf::Color color;
};