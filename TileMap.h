#pragma once

#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable {
public:
	bool load(sf::Vector2u tileSize, std::vector<int> tiles, int width, int height, int n);
	bool update(std::vector<int> tiles);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray m_vertices;
	int W, H, N;
};
