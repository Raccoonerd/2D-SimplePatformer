#pragma once
#include "Entity.h"
#include "TileMap.h"

class Player :
    public Entity
{
private:

    float speed = 150.f;
	float jumpForce = 300.f;
	float gravity = 9.81f;
	bool isOnGround = false;

public:

	Player(const sf::Texture& texture, const sf::Vector2f startPos);

	void handleInput();
	void update(float dt, const TileMap& tileMap);
	void update(float dt) override {};

private:

	void resolveCollision(const TileMap& tileMap, bool horizontal);


};

