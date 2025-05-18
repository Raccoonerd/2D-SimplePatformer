#pragma once
#include "lib.h"
#include "TileMap.h"
#include "Player.h"


class Level
{
private:
	TileMap tileMap;
	std::unique_ptr<Player> player;
	//std::vector<std::unique_ptr<Enemy>> enemies;
	//std::vector<std::unique_ptr<Collectible>> collectibles;

	sf::View camera;

public:
	bool load(const std::string& tilemapFile, const sf::Texture& playerTexture,
		const sf::Texture& enemyTexture, const sf::Texture& collectibleTexture);
	void update(float dt);
	void draw(sf::RenderWindow& window);
	Player* getPlayer() const;

private:
	void updateCamera();
};


