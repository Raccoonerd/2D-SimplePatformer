#pragma once
#include "lib.h"

class Entity
{
protected:
	
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Sprite* sprite;

public:

	virtual ~Entity() { delete sprite; };

	virtual void update(float dt) = 0;

	virtual void draw(sf::RenderWindow& window) const;

	sf::Vector2f getPosition() const;

	void setPosition(sf::Vector2f pos);

	sf::FloatRect getBounds() const;

	virtual void onCollision(Entity* other) = 0;

	virtual bool isActive() const;

};

