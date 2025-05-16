#include "TileMap.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Tile Map Example");
	window.setFramerateLimit(60);

	sf::Texture tileTexture;
	if (!tileTexture.loadFromFile("Assets/Sprites/tiles.png"))
	{
		return -1;
	}

	TileMap tilemap("Assets/LevelsMaps/maplvl1.ini", tileTexture);

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		window.clear();

		tilemap.draw(window);

		window.display();
	}

	return 0;
	
}