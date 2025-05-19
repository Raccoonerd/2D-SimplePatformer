#include "Level.h"

bool Level::load(const std::string& tilemapFile, const sf::Texture& playerTexture, 
	const sf::Texture& enemyTexture, const sf::Texture& collectibleTexture)
{
	if (!tileMap.loadFromFile(tilemapFile))
	{
		return false;
	}

	player = std::make_unique<Player>(playerTexture, sf::Vector2f({ 64.f, 64.f }));

	//enemies.push_back(std::make_unique<Enemy>(enemyTexture, sf::Vector2f({ 128.f, 128.f })));

	//collectibles.push_back(std::make_unique<Collectible>(collectibleTexture, sf::Vector2f({ 192.f, 192.f })));

	camera.setSize({ 800.f, 600.f });
	camera.setCenter(player->getPosition());

	return true;
}

void Level::update(float dt)
{
	if (player)
	{
		player->update(dt, tileMap);
	}

	/*for (auto& enemy : enemies)
	{
		enemy->update(dt);
	}*/

	/*for (auto& col : collectibles)
	{
		if (col->isActive() && player->getBounds().findIntersection(col->getBounds())) 
		{
			col->collect();
		}
	}*/

	updateCamera();

}


void Level::draw(sf::RenderWindow& window)
{
	window.setView(camera);

	tileMap.draw(window);

	/*for (const auto& col : collectibles)
	{
		if (col->isActive())
		{
			col->draw(window);
		}
	}*/

	/*for (const auto& enemy: enemies)
	{
		enemy->draw(window);
	}*/

	if (player)
	{
		player->draw(window);
	}
}

Player* Level::getPlayer() const
{
	return player.get();
}

void Level::updateCamera()
{
	sf::Vector2f playerPos = player->getPosition();
	sf::Vector2f viewCenter = playerPos;
	viewCenter.y = std::max(viewCenter.y, 300.f);

	camera.setCenter(viewCenter);
}