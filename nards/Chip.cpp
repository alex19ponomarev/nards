#include "Chip.h"

sf::Vector2f Chip::fieldCoord[24] = {
	sf::Vector2f(22.f,925.f), sf::Vector2f(87.f,925.f), sf::Vector2f(152.f,925.f), sf::Vector2f(217.f,925.f),
	sf::Vector2f(281.f,925.f), sf::Vector2f(346.f,925.f), sf::Vector2f(607.f,925.f), sf::Vector2f(672.f,925.f),
	sf::Vector2f(736.f,925.f), sf::Vector2f(801.f,925.f), sf::Vector2f(866.f,925.f), sf::Vector2f(931.f,925.f),

	sf::Vector2f(931.f,26.f), sf::Vector2f(866.f,26.f), sf::Vector2f(801.f,26.f), sf::Vector2f(736.f,26.f),
	sf::Vector2f(672.f,26.f), sf::Vector2f(607.f,26.f), sf::Vector2f(346.f,26.f), sf::Vector2f(281.f,26.f),
	sf::Vector2f(217.f,26.f), sf::Vector2f(152.f,26.f), sf::Vector2f(87.f,26.f), sf::Vector2f(22.f,26.f)
};

Chip::Chip(sf::Color color) :
	shape(22.f)
{
	shape.setFillColor(color);
	defaultColor = color;
}

void Chip::setPosition(sf::Vector2f position)
{
	shape.setPosition(position);
}

void Chip::render(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Chip::move(int position, int count)
{
	if (position >= 0 && position <= 11) {
		shape.setPosition(sf::Vector2f(fieldCoord[position].x - count * 44.f, fieldCoord[position].y ));
	}
	else {
		shape.setPosition(sf::Vector2f(fieldCoord[position].x + count * 44.f, fieldCoord[position].y ));
	}
	
}

void Chip::setStatus(Status status)
{
	this->status = status;
	if (status == Status::HOVER) {
		shape.setFillColor(sf::Color::Blue);
	}
	else if (status == Status::ACTIVE) {
		shape.setFillColor(sf::Color::Green);
	}
	else if (status == Status::DEFAULT) {
		shape.setFillColor(defaultColor);
	}
}

Status Chip::getStatus()
{
	return status;
}

sf::Vector2f Chip::getPosition()
{
	return shape.getPosition();
}


