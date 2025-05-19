#include "Entity.h"

Entity::Entity(const sf::Texture& texture, const sf::Vector2f pos)
{
	position = pos;
	velocity = { 0.f,0.f };
	sprite = new sf::Sprite(texture);
	sprite->setPosition(pos);
}

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