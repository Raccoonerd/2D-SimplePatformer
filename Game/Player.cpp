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
    int startX = static_cast<int>(playerBounds.position.x / tileSize);
    int endX = static_cast<int>((playerBounds.position.x + playerBounds.size.x) / tileSize);
    int startY = static_cast<int>(playerBounds.position.y / tileSize);
    int endY = static_cast<int>((playerBounds.position.y + playerBounds.size.y) / tileSize);

    constexpr float epsilon = 0.001f;

    for (int y = startY; y <= endY; y++)
    {
        for (int x = startX; x <= endX; x++)
        {
            const Tile* tile = tileMap.getTileAt({ x * (float)tileSize, y * (float)tileSize });
            if (tile && tile->isSolid)
            {
                sf::FloatRect tileBounds = tile->getBounds();

                if (playerBounds.position.x < tileBounds.position.x + tileBounds.size.x &&
                    playerBounds.position.x + playerBounds.size.x > tileBounds.position.x &&
                    playerBounds.position.y < tileBounds.position.y + tileBounds.size.y &&
                    playerBounds.position.y + playerBounds.size.y > tileBounds.position.y)

                {
                    if (horizontal)
                    {
                        if (velocity.x > 0)
                            velocity.x = 0;
                        //position.x = tileBounds.position.x - playerBounds.size.x - epsilon;
                        else if (velocity.x < 0)
                            velocity.x = 0;
                            //position.x = tileBounds.position.x + tileBounds.size.x + epsilon;
                        velocity.x = 0.f;
                    }
                    else
                    {
                        if (velocity.y > 0)
                        {
							velocity.y = 0;
							position.y = tileBounds.position.y - playerBounds.size.y;
                            isOnGround = true;
                        }
                        else if (velocity.y < 0)
							velocity.y = 0;
                            //position.y = tileBounds.position.y + tileBounds.size.y + epsilon;
                        velocity.y = 0.f;
                    }
                    sprite->setPosition(position);
                    playerBounds = getBounds();
                    return;
                }
            }
        }
    }
}
