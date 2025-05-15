#pragma once
#include "Tile.h"

class TileMap
{
private:
	std::vector<Tile> tiles;
	unsigned int width = 0;
	unsigned int height = 0;

	const unsigned int tileSize = 32;

public:

	TileMap() = default;
	TileMap(const std::string& filename, const sf::Texture& tileTexture);
	~TileMap() = default;
	void draw(sf::RenderWindow& window) const;
	const Tile* getTileAt(sf::Vector2f position) const;
	unsigned int getTileSize() const;
	sf::Vector2u getMapSize() const;
};

