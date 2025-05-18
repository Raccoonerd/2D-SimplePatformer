#include "Entity.h"

void Entity::draw(sf::RenderWindow& window) const
{
	window.draw(*sprite);
}

sf::Vector2f Entity::getPosition() const
{
	return position;
}

void Entity::setPosition(sf::Vector2f pos)
{
	position = pos;
	sprite->setPosition(pos);
}

sf::FloatRect Entity::getBounds() const
{
	return sprite->getGlobalBounds();
}

bool Entity::isActive() const
{
	return true;
}