#include "TileMap.h"

TileMap::TileMap(const std::string& filename, const sf::Texture& tileTexture)
{
	tiles.clear();
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}

	std::string line;
	int y = 0;

	while (std::getline(file, line))
	{
		width = std::max(width, static_cast<unsigned int>(line.length()));
		for (unsigned int x = 0; x < line.length(); ++x)
		{
			char symbol = line[x];
			TileType type = TileType::Empty;

			switch (symbol)
			{
				case '#': type = TileType::Ground; break;
				case '=': type = TileType::Platform; break;
				case '^': type = TileType::Spikes; break;
				case '~': type = TileType::Background; break;
				case '.': default: type = TileType::Empty; break;
			}
			sf::Vector2f position(x * tileSize, y * tileSize);
			tiles.emplace_back(type, tileTexture, position);
		}

		++y;

	}
	height = y;
	file.close();
}

void TileMap::draw(sf::RenderWindow& window) const
{
	for (const auto& tile : tiles)
	{
		tile.draw(window);
	}
}

const Tile* TileMap::getTileAt(sf::Vector2f position) const
{
	int x = static_cast<int>(position.x / tileSize);
	int y = static_cast<int>(position.y / tileSize);

	if (x < 0 || y < 0 || x >= static_cast<int>(width) || y >= static_cast<int>(height))
	{
		return nullptr;
	}

	return &tiles[y * width + x];
}

sf::Vector2u TileMap::getMapSize() const
{
	return sf::Vector2u(width, height);
}