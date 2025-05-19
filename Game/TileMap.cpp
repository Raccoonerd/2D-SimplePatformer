#include "TileMap.h"

bool TileMap::loadFromFile(const std::string& filename, const sf::Texture& texture)
{
	tiles.clear();
	tilesetTexture = &texture;

	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cerr << "Error opening file: " << filename << std::endl;
		return false;
	}

	std::vector<std::string> lines;
	std::string line;
	int y = 0;

	while (std::getline(file, line))
	{
		width = std::max(width, static_cast<unsigned int>(line.size()));
		lines.push_back(line);
	}
	height = static_cast<unsigned int>(lines.size());
	file.close();


	// Uzupe³nij ka¿d¹ liniê do szerokoœci width i wype³nij tiles
	for (unsigned int y = 0; y < height; ++y)
	{
		const std::string& row = lines[y];
		for (unsigned int x = 0; x < width; ++x)
		{
			char symbol = (x < row.length()) ? row[x] : '.'; // brakuj¹ce znaki jako puste
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
			tiles.emplace_back(type, texture, position);
		}
	}

	return true;
}

void TileMap::draw(sf::RenderWindow& window) const
{
	for (const auto& tile : tiles)
	{
		tile.draw(window);
	}

	//std::cout << tiles.size() << std::endl;
}

const Tile* TileMap::getTileAt(sf::Vector2f position) const
{
	int x = static_cast<int>(position.x / tileSize);
	int y = static_cast<int>(position.y / tileSize);

	if (x < 0 || y < 0 || x >= static_cast<int>(width) || y >= static_cast<int>(height))
	{
		return nullptr;
	}

	size_t index = static_cast<size_t>(y) * width + x;
	/*if (index >= tiles.size())
	{
		return nullptr;
	}*/

	return &tiles[index];
}

unsigned int TileMap::getTileSize() const
{
	return tileSize;
}

sf::Vector2u TileMap::getMapSize() const
{
	return sf::Vector2u(width, height);
}