#pragma once
#include <SFML/Graphics.hpp>

class Tile
{
    public:
        Tile( int kind = 0, sf::Color color = sf::Color::White)
            : kind(kind), color(color) {}
        
        const int getKind() const {return kind; }
        
        const sf::Color& getColor() const {return color; }

    private:
        int kind;
        sf::Color color;
};