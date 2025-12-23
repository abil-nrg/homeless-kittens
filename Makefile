CXX = g++
CXXFLAGS = -Wall -std=c++17 -I include
SFML = -lsfml-graphics -lsfml-window -lsfml-system
SRC = src/main.cpp src/Game.cpp src/Tilemap.cpp

main: $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o main $(SFML)
	./main

clean:
	rm -f main