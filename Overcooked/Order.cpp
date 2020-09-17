#include "Order.h"

void Order::resetFieldsPosition()
{
	timerBar.setPosition(x, y + height);
	outer.setPosition(x, y);
	inner.setPosition(x + 3, y + 3);
	int shift = 0;
	for (auto it = std::begin(foodList); it != std::end(foodList); it++)
	{
		shift += TILE_SIZE / 2;
		(*it)->setPosition((x + shift + 3), y + TILE_SIZE / 2 + 3);
		shift += TILE_SIZE / 2;
	}
}

Order::Order(sf::Texture& t)
{
	timerBar.setFillColor(sf::Color(255, 0, 0));
	outer.setFillColor(sf::Color(255, 216, 0));
	inner.setFillColor(sf::Color(0, 0, 0));
	outer.setSize(sf::Vector2f(width, height));
	inner.setSize(sf::Vector2f(width - 6, height - 6));
	resetFieldsPosition();
}

Order::~Order()
{
	while (foodList.size())
	{
		delete foodList.front();
		foodList.pop_front();
	}
}

bool Order::isValid()
{
	if (completed)
		return false;
	return (timer < orderTime) ? true : false;
}

void Order::complete()
{
	completed = true;
}

bool Order::isCompleted()
{
	return completed;
}

void Order::update(float time)
{
	if (isValid())
	{
		timer += time;
	}
	else
	{
		return;
	}
	timerBar.setSize(sf::Vector2f(width - (width * (double)timer) / orderTime, 5));
}

void Order::draw(sf::RenderWindow& rw)
{
	rw.draw(outer);
	rw.draw(inner);
	for (auto it = std::begin(foodList); it != std::end(foodList); it++)
	{
		rw.draw((*it)->getSprite());
	}
	rw.draw(timerBar);
}

void Order::setPosition(float _x, float _y)
{
	x = _x;
	y = _y;
	resetFieldsPosition();
}

float Order::getHeight()
{
	return height;
}

float Order::getWidth()
{
	return width;
}

std::list<Food*> Order::getList()
{
	return foodList;
}

sf::Vector2f Order::getPosition()
{
	return sf::Vector2f(x, y);
}

int Order::getOrderTime()
{
	return orderTime;
}

int Order::getTips()
{
	int additionalTips = (orderTime / timer) * tips;
	if (additionalTips > 30)
		additionalTips = 30;
	return tips + additionalTips;
}

void OrderQueue::resetPosition(Order* order)
{
	if (queue.size() == 0)
	{
		return;
	}
	auto it = std::find(std::begin(queue), std::end(queue), order);
	if (it == std::begin(queue))
	{
		(*it)->setPosition(x, y);
		return;
	}
	auto previous = std::prev(it);
	float _x = (*previous)->getPosition().x;
	float _y = (*previous)->getPosition().y;
	int _height = (*previous)->getHeight();
	(*it)->setPosition(_x, _y + _height + 6);
}

OrderQueue::~OrderQueue()
{
	while (queue.size())
	{
		delete queue.front();
		queue.pop_front();
	}
}

void OrderQueue::add(Order* order)
{
	queue.push_back(order);
	resetPosition(order);
}

void OrderQueue::update(float time)
{
	std::vector<std::list<Order*>::iterator> invalidOrders;
	for (auto it = std::begin(queue); it != std::end(queue); it++)
	{
		(*it)->update(time);
		if (!(*it)->isValid())
		{
			invalidOrders.push_back(it);
		}
	}
	for (auto it : invalidOrders)
	{
		if ((*it)->isCompleted())
			totalTips += (*it)->getTips();
		else if(totalTips > 0)
			totalTips -= 10;
		queue.erase(it);
	}
	for (const auto& order : queue)
	{
		resetPosition(order);
	}
}

void OrderQueue::draw(sf::RenderWindow& rw)
{
	for (const auto& order : queue)
	{
		order->draw(rw);
	}
}

void OrderQueue::setPosition(float _x, float _y)
{
	x = _x;
	y = _y;
	for (const auto& order : queue)
	{
		resetPosition(order);
	}
}

std::list<Order*> OrderQueue::getOrders()
{
	return queue;
}

int OrderQueue::getTips()
{
	return totalTips;
}

TomatoSoupOrder::TomatoSoupOrder(sf::Texture& t) : Order(t)
{
	foodList.push_back(new Tomato(t));
	foodList.push_back(new Tomato(t));
	foodList.push_back(new Tomato(t));
	for (auto it = std::begin(foodList); it != std::end(foodList); it++)
	{
		(*it)->setCooked();
	}
}

MushroomSoupOrder::MushroomSoupOrder(sf::Texture& t) : Order(t)
{
	foodList.push_back(new Mushroom(t));
	foodList.push_back(new Mushroom(t));
	foodList.push_back(new Mushroom(t));
	for (auto it = std::begin(foodList); it != std::end(foodList); it++)
	{
		(*it)->setCooked();
	}
	tips = 6;
}

OnionSoupOrder::OnionSoupOrder(sf::Texture& t) : Order(t)
{
	foodList.push_back(new Onion(t));
	foodList.push_back(new Onion(t));
	foodList.push_back(new Onion(t));
	for (auto it = std::begin(foodList); it != std::end(foodList); it++)
	{
		(*it)->setCooked();
	}
	tips = 8;
}

RandomOrderFactory::RandomOrderFactory(sf::Texture& _texture) : texture(_texture)
{
	srand(time(0));
	rand();
}

Order* RandomOrderFactory::create()
{
	switch (rand() % 3)
	{
	case 0:
		return new TomatoSoupOrder(texture);
		break;
	case 1:
		return new MushroomSoupOrder(texture);
		break;
	case 2:
		return new OnionSoupOrder(texture);
		break;
	default:
		break;
	}
}
