#include "GameStats.h"

GameStats::GameStats(sf::Texture& _texture, float _x, float _y)
{
	font.loadFromFile("Fonts/lucida.ttf");

	tips = new StatObject(_texture, font, 7, 0, _x + 6, _y);
	timer = new StatObject(_texture, font, 8, 0, _x + 2 * TILE_SIZE, _y);

	background.setFillColor(sf::Color(207, 185, 140));
	background.setSize(sf::Vector2f(TILE_SIZE * 3 + 6, TILE_SIZE));
	background.setPosition(_x, _y);
}

GameStats::~GameStats()
{
	delete tips;
	delete timer;
}

void GameStats::update(float _time, int _tips)
{
	time += _time;
	timer->setText(std::to_string((int)time / 2000));
	tips->setText(std::to_string(_tips));
}

void GameStats::draw(sf::RenderWindow& rw)
{
	rw.draw(background);
	tips->draw(rw);
	timer->draw(rw);
}

StatObject::StatObject(sf::Texture& _texture, sf::Font& _font, int tileX, int tileY, float _x, float _y)
{
	sprite.setTexture(_texture);
	sprite.setTextureRect(sf::IntRect(tileX * TILE_SIZE, tileY * TILE_SIZE, TILE_SIZE, TILE_SIZE));
	sprite.setOrigin(TILE_SIZE / 2, TILE_SIZE / 2);
	sprite.setPosition(_x + TILE_SIZE / 2, _y + TILE_SIZE / 2);

	text.setFont(_font);
	text.setOutlineColor(sf::Color(0, 0, 0));
	text.setOutlineThickness(1);
	text.setFillColor(sf::Color(255, 255, 255));
	text.setCharacterSize(TILE_SIZE - 16);
	text.setString("");
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition(_x + TILE_SIZE / 2, _y + TILE_SIZE / 2);
}

void StatObject::setText(std::string _text)
{
	text.setString(_text);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition(text.getPosition().x, text.getPosition().y);
}

void StatObject::draw(sf::RenderWindow& rw)
{
	rw.draw(sprite);
	rw.draw(text);
}
