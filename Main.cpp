#include <SFML/Graphics.hpp>

#include "TileMap.h"
#include "CellGrid.h"
#include "thread"
#include "chrono"

//TODO: maybe someday control these values with a GUI?
#define WIDTH 100											//width of grid 
#define HEIGHT 100											//height of grid
#define N 15												//number of states for cells
#define HOOD 1												//neighborhood
#define SCALE 10											//Scale of pixels


int main() {

	CellGrid grid;
	TileMap map;

	grid.load(WIDTH, HEIGHT, N);
	grid.makeNoise();

	if (!map.load(sf::Vector2u(SCALE, SCALE), grid.cells, WIDTH, HEIGHT, N)) return -1;

	sf::RenderWindow window(sf::VideoMode(WIDTH * SCALE, HEIGHT * SCALE), "Fluid");
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}

		grid.step(HOOD);
		map.update(grid.cells);

		std::this_thread::sleep_for(std::chrono::milliseconds(30));
		//Set background color here
		window.clear(sf::Color(0, 0, 0));
		window.draw(map);
		window.display();
	}
	return 0;
}