#include "Tile.h"

sf::Sprite* Tile::sprite = nullptr;

Tile::Tile(TileType t, sf::Vector2f position) : type(t)
{
	isSolid = (t == TileType::Ground || t == TileType::Platform || t == TileType::Spikes);

	sprite->setPosition(position);

	switch (type)
	{
	case TileType::Empty:
		break;
	case TileType::Ground:
		sprite->setTextureRect(sf::IntRect({ 0,0 }, { 32,32 }));
		break;
	case TileType::Platform:
		sprite->setTextureRect(sf::IntRect({ 32,0 }, { 32,32 }));
		break;
	case TileType::Spikes:
		sprite->setTextureRect(sf::IntRect({ 64,0 }, { 32,32 }));
		break;
	case TileType::Background:
		sprite->setTextureRect(sf::IntRect({ 96,0 }, { 32,32 }));
		break;
	default:
		break;
	}
}


void Tile::draw(sf::RenderWindow& window) const
{
	if (type != TileType::Empty)
	{
		window.draw(*sprite);
	}
}

sf::FloatRect Tile::getBounds() const
{
	return sprite->getGlobalBounds();
}