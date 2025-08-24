#pragma once
#include <SFML/Graphics.hpp>

enum Status
{
	DEFAULT,
	ACTIVE,
	HOVER
};

class Chip
{
	sf::CircleShape shape;
	Status status = DEFAULT;
	sf::Color defaultColor;

public:
	static sf::Vector2f fieldCoord[24];

	Chip(sf::Color color);
	void setPosition(sf::Vector2f position);
	void render(sf::RenderWindow& window);
	void move(int position, int count);
	void setStatus(Status status);
	Status getStatus();
	sf::Vector2f getPosition();

};

