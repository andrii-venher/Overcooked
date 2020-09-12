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

void Order::setOrderTime(int _time)
{
	orderTime = _time;
}

Order::Order(Texture& t, int _capacity)
{
	timerBar.setFillColor(Color(255, 0, 0));
	outer.setFillColor(Color(255, 216, 0));
	inner.setFillColor(Color(0, 0, 0));
	outer.setSize(Vector2f(width, height));
	inner.setSize(Vector2f(width - 6, height - 6));
	resetFieldsPosition();
}

bool Order::isValid()
{
	return (timer < orderTime) ? true : false;
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
	timerBar.setSize(Vector2f(width - (width * (double)timer) / orderTime, 5));
}

void Order::draw(RenderWindow& rw)
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

Vector2f Order::getPosition()
{
	return Vector2f(x, y);
}

TomatoSoupOrder::TomatoSoupOrder(Texture& t) : Order(t, 3)
{
	foodList.push_back(new Tomato(t));
	foodList.push_back(new Tomato(t));
	foodList.push_back(new Tomato(t));
	for (auto it = std::begin(foodList); it != std::end(foodList); it++)
	{
		(*it)->setCooked();
	}
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
		queue.erase(it);
	}
	for (const auto& order : queue)
	{
		resetPosition(order);
	}
}

void OrderQueue::draw(RenderWindow& rw)
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

//TomatoSoupOrder1::TomatoSoupOrder1(Texture& t) : Order(t, 3)
//{
//	foodList.push_back(new Tomato(t));
//	foodList.push_back(new Tomato(t));
//	foodList.push_back(new Tomato(t));
//
//	for (auto it = std::begin(foodList); it != std::end(foodList); it++)
//	{
//		(*it)->setCooked();
//	}
//
//	setOrderTime(10000);
//}