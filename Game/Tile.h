#pragma once
#include "lib.h"

enum class TileType
{
	Empty,
	Ground,
	Platform,
	Spikes,
	Background,
};

class Tile
{
public:

	TileType type = TileType::Empty;
	bool isSolid = false;
	sf::Sprite* sprite;


	Tile(TileType t, const sf::Texture& texture, sf::Vector2f position);

	~Tile() = default;

	void draw(sf::RenderWindow& window) const;

	sf::FloatRect getBounds() const;

};

