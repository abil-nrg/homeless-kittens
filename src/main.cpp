#include <SFML/Graphics.hpp>
#include <iostream>

int main(){
    //main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Homeless Kittens");
    window.setVerticalSyncEnabled(true); // set freq same as monitor refresh rate

    const float cursor_size = 15.f; //radius
    sf::CircleShape cursor(cursor_size);

    cursor.setFillColor(sf::Color::Green);
    cursor.setPosition(400.f, 300.f);

    const float speed = 15.f;

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
            
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                cursor.move(0.f, -speed);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                cursor.move(0.f, speed);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                cursor.move(-speed, 0.f);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                cursor.move(speed, 0.f);
            }

            sf::Vector2i localPos = sf::Mouse::getPosition(window);
            cursor.setPosition({localPos.x - cursor_size , localPos.y - cursor_size});
        }

        window.clear();
        window.draw(cursor);
        window.display();
    }
    return 0;
}