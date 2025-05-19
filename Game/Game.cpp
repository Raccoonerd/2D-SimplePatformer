#include "Game.h"

Game::Game() : window(sf::VideoMode({ 800, 600 }), "Platformer Game")
{
	window.setFramerateLimit(60);
}

bool Game::init()
{

	if (!playerTexture.loadFromFile("Assets/Sprites/player.png") ||
		/*!enemyTexture.loadFromFile("Assets/Sprites/enemy.png") ||
		!coinTexture.loadFromFile("Assets/Sprites/coin.png") ||*/
		!tilesetTexture.loadFromFile("Assets/Sprites/tileset.png"))
	{
		return false;
	}

	
	if (!level.load("Assets/LevelsMaps/maplvl1.ini", playerTexture, enemyTexture, coinTexture, tilesetTexture))
	{
		return false;
	}

	return true;
}

void Game::run()
{
	while (window.isOpen() && isRunning)
	{
		float dt = clock.restart().asSeconds();
		handleEvents();
		update(dt);
		render();
	}
}

void Game::handleEvents()
{
	while (const std::optional event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			window.close();
		}
	}
}

void Game::update(float dt)
{
	level.update(dt);
}

void Game::render()
{

	window.clear();
	level.draw(window);
	window.display();
}

