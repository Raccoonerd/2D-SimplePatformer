#pragma once
#include "Level.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Clock clock;

	Level level;

	sf::Texture playerTexture;
	sf::Texture enemyTexture;
	sf::Texture coinTexture;
	sf::Texture tilesetTexture;

	bool isRunning = 1;

public:
	Game();

	bool init();
	void run();

private:
	void handleEvents();
	void update(float dt);
	void render();
};

