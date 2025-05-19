#pragma once
#include "Tile.h"

class TileMap
{
private:
	std::vector<Tile> tiles;
	unsigned int width = 0;
	unsigned int height = 0;

	const sf::Texture* tilesetTexture = nullptr;

	const unsigned int tileSize = 32;

public:

	TileMap() = default;
	~TileMap() = default;
	bool loadFromFile(const std::string& filename, const sf::Texture& texture);
	void draw(sf::RenderWindow& window) const;
	const Tile* getTileAt(sf::Vector2f position) const;
	unsigned int getTileSize() const;
	sf::Vector2u getMapSize() const;
};

