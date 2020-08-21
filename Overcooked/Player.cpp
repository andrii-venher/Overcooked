#include "Player.h"

Player::Player(Texture& texture, float _x, float _y, IntRect _tileRect, std::list<TiledObject*>& _objects) : 
	TiledObject(texture, _x, _y, _tileRect), 
	objects(_objects)
{
	state = States::STAY;

	xSpeed = 0;
	ySpeed = 0;

	//inHands = nullptr;
	inHands = new TiledObject(texture, _x, _y, IntRect(32, 0, 32, 32));
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
		sprite.setRotation(270);
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
	case Player::States::NEEDS_UPDATE:
	{
		switch (getRotation())
		{
		case Rotations::LEFT:
			inHands->setPosition(x - inHands->getTileRect().width, y);
			break;
		case Rotations::UP:
			inHands->setPosition(x, y - inHands->getTileRect().height);
			break;
		case Rotations::RIGHT:
			inHands->setPosition(x + inHands->getTileRect().width, y);
			break;
		case Rotations::DOWN:
			inHands->setPosition(x, y + inHands->getTileRect().height);
			break;
		default:
			break;
		}
	}
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
		if (Keyboard::isKeyPressed(Keyboard::T))
		{
			std::cout << (int)x / 32 << " " << (int)y / 32 << "\n";
			takeIntoHands();
			state = States::NEEDS_UPDATE;
		}
	}
}

Sprite Player::getSprite()
{
	return sprite;
}

Sprite Player::getInHandsSprite()
{
	if (inHands)
		return inHands->getSprite();
	else
		return Sprite();
}

void Player::takeIntoHands()
{
	int playerXTile;
	int playerYTile;
	int objXTile;
	int objYTile;
	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		playerXTile = (x - 0) / 32;
		playerYTile = (y - 0) / 32;
		objXTile = ((*it)->getSprite().getPosition().x - 0) / 32;
		objYTile = ((*it)->getSprite().getPosition().y - 0) / 32;
		if ((getRotation() == Rotations::LEFT && playerXTile == objXTile + 1 && playerYTile == objYTile) ||
			(getRotation() == Rotations::UP && playerXTile == objXTile && playerYTile == objYTile + 1) ||
			(getRotation() == Rotations::RIGHT && playerXTile == objXTile - 1 && playerYTile == objYTile) ||
			(getRotation() == Rotations::DOWN && playerXTile == objXTile && playerYTile == objYTile - 1))
		{
			delete inHands;
			inHands = *it;
			objects.erase(it);
			break;
		}
		/*if ((int)(*it)->getSprite().getPosition().x / 32 == (int)x / 32 && (int)(*it)->getSprite().getPosition().y / 32 == (int)y / 32 + 1)
		{
			delete inHands;
			inHands = *it;
			objects.erase(it);
			break;
		}*/
	}
}
