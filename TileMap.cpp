#include "TileMap.h"

//Adapted from https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php
bool TileMap::load(sf::Vector2u tileSize, std::vector<int> tiles, int width, int height, int n) {

	N = n;
	W = width;
	H = height;

	//Set the size of the array to fit the screen
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * height * 4);

	int x = 0;
	int y = 0;
	// populate the vertex array, with one quad per tile
	for (std::vector<int>::iterator it = tiles.begin(); it != tiles.end(); ++it) {

		// get a pointer to the current tile's quad
		sf::Vertex* quad = &m_vertices[(x + y * width) * 4];

		// define its 4 corners
		quad[0].position = sf::Vector2f(x * tileSize.x, y * tileSize.y);
		quad[1].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
		quad[2].position = sf::Vector2f((x + 1) * tileSize.x, (y + 1) * tileSize.y);
		quad[3].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);

		int val = (*it) * (255 / (N - 1));

		// define its color
		quad[0].color = sf::Color(125, 0, 255, val);
		quad[1].color = sf::Color(125, 0, 255, val);
		quad[2].color = sf::Color(125, 0, 255, val);
		quad[3].color = sf::Color(125, 0, 255, val);

		//update coords
		x++;
		x %= width;
		if (x == 0) y++;
	}

	return true;
}

//updates the colors of the vertices to reflect the data in a given array
bool TileMap::update(std::vector<int> tiles) {

	int x = 0;
	int y = 0;
	// populate the vertex array, with one quad per tile
	for (std::vector<int>::iterator it = tiles.begin(); it != tiles.end(); ++it) {

		// get a pointer to the current tile's quad
		sf::Vertex* quad = &m_vertices[(x + y * W) * 4];

		int val = (*it) * (255 / (N - 1));
		// define its new color
		quad[0].color = sf::Color(0, 106, 181, val);
		quad[1].color = sf::Color(0, 106, 181, val);
		quad[2].color = sf::Color(0, 106, 181, val);
		quad[3].color = sf::Color(0, 106, 181, val);

		//update coords
		x++;
		x %= W;
		if (x == 0) y++;
	}
	return true;
}

void TileMap::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	// apply the transform
	states.transform *= getTransform();

	// draw the vertex array
	target.draw(m_vertices, states);
}

