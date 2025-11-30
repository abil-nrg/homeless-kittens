CXX = g++
CXXFLAGS = -Wall -std=c++17
SFML = -lsfml-graphics -lsfml-window -lsfml-system
SRC = src/main.cpp

main: $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o main $(SFML)

clean:
	rm -f main