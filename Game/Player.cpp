#include "Player.h"

Player::Player(const sf::Texture& texture, const sf::Vector2f startPos)
	: Entity(texture, startPos)
{
	sprite = new sf::Sprite(texture);
	sprite->setTextureRect(sf::IntRect({ 0, 0 }, {32, 32}));
	position = startPos;	
	sprite->setPosition(startPos);
	velocity = { 0.f, 0.f };
};

void Player::handleInput()
{
	velocity.x = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		//std::cout << "Left\n";
		velocity.x -= speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		//std::cout << "Right\n";
		velocity.x += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && isOnGround)
	{
		velocity.y = -jumpForce;
		isOnGround = false;
	}
}

void Player::update(float dt, const TileMap& tileMap)
{
	handleInput();

	velocity.y += gravity * dt;

	position.x +=  velocity.x * dt;
	resolveCollision(tileMap, true);

	position.y += velocity.y * dt;
	resolveCollision(tileMap, false);

	sprite->setPosition(position);
}

void Player::resolveCollision(const TileMap& tileMap, bool horizontal)
{
    sf::FloatRect playerBounds = getBounds();
	sf::Vector2f positionBefore = sprite->getPosition();

    int tileSize = tileMap.getTileSize();
    int startX = static_cast<int>(playerBounds.left / tileSize);
    int endX = static_cast<int>((playerBounds.left + playerBounds.width) / tileSize);
    int startY = static_cast<int>(playerBounds.top / tileSize);
    int endY = static_cast<int>((playerBounds.top + playerBounds.height) / tileSize);

    constexpr float epsilon = 0.001f;

    for (int y = startY; y <= endY; y++)
    {
        for (int x = startX; x <= endX; x++)
        {
            const Tile* tile = tileMap.getTileAt({ x * (float)tileSize, y * (float)tileSize });
            if (tile && tile->isSolid)
            {
                sf::FloatRect tileBounds = tile->getBounds();

                if (playerBounds.left < tileBounds.left + tileBounds.width &&
                    playerBounds.left + playerBounds.width > tileBounds.left &&
                    playerBounds.top < tileBounds.top + tileBounds.height &&
                    playerBounds.top + playerBounds.height > tileBounds.top)
                {
                    if (horizontal)
                    {
                        if (velocity.x > 0) // Moving right
                        {
                            position.x = tileBounds.left - playerBounds.width - epsilon;
                            velocity.x = 0.f;
                        }
                        else if (velocity.x < 0) // Moving left
                        {
                            position.x = tileBounds.left + tileBounds.width + epsilon;
                            velocity.x = 0.f;
                        }
                        // The specific velocity.x = 0.f assignments above make the unconditional one below redundant.
                        // The original unconditional velocity.x = 0.f; is removed by not re-adding it here.
                    }
                    else // Vertical collision
                    {
                        if (velocity.y > 0) // Moving down
                        {
							velocity.y = 0; 
							position.y = tileBounds.top - playerBounds.height; // Corrected for sf::FloatRect
                            isOnGround = true;
                        }
                        else if (velocity.y < 0) // Moving up
                        {
							velocity.y = 0.f; // Ensure it's set, using .f for consistency
                            position.y = tileBounds.top + tileBounds.height + epsilon; // Modified as per task
                        }
                        // The unconditional velocity.y = 0.f has been removed as each branch now handles it.
                    }
                    sprite->setPosition(position);
                    playerBounds = getBounds();
                    return;
                }
            }
        }
    }
}
