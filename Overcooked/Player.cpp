#include "Player.h"

Player::Player(Texture& texture, IntRect _tileRect, float _x, float _y) : TiledObject(texture, _x, _y, _tileRect)
{
	state = States::STAY;

	xSpeed = 0;
	ySpeed = 0;

	inHands = new TiledObject(texture, _x, _y, IntRect(32, 32, 32, 32));
}

void Player::update(float time)
{
	trackControls();

	switch (state)
	{
	case Player::States::LEFT:
		xSpeed = -0.1;
		ySpeed = 0;
		sprite.setRotation(90);
		break;
	case Player::States::UP:
		ySpeed = -0.1;
		xSpeed = 0;
		sprite.setRotation(180);
		break;
	case Player::States::RIGHT:
		xSpeed = 0.1;
		ySpeed = 0;
		sprite.setRotation(-90);
		break;
	case Player::States::DOWN:
		ySpeed = 0.1;
		xSpeed = 0;
		sprite.setRotation(0);
		break;
	case Player::States::STAY:
		xSpeed = ySpeed = 0;
		break;
	default:
		break;
	}

	x += xSpeed * time;
	y += ySpeed * time;

	sprite.setPosition(x, y);

	switch (state)
	{
	case Player::States::LEFT:
		inHands->setPosition(x - inHands->getTileRect().width, y);
		break;
	case Player::States::UP:
		inHands->setPosition(x, y - inHands->getTileRect().height);
		break;
	case Player::States::RIGHT:
		inHands->setPosition(x + inHands->getTileRect().width, y);
		break;
	case Player::States::DOWN:
		inHands->setPosition(x, y + inHands->getTileRect().height);
		break;
	case Player::States::STAY:
		break;
	default:
		break;
	}

	state = States::STAY;
}

void Player::trackControls()
{
	if (Keyboard::isKeyPressed)
	{
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			state = States::LEFT;
		}
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			state = States::UP;
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			state = States::RIGHT;
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			state = States::DOWN;
		}
	}
}

Sprite Player::getSprite()
{
	return sprite;
}

Sprite Player::getInHands()
{
	return inHands->getSprite();
}
