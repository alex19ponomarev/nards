#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Chip.h"
#include "Dice.h"

class Game
{
	sf::RenderWindow window;
	sf::Event event;
	std::vector<Chip> field[24];
	std::vector<Dice> dices;
	sf::Texture bgTexture, buttonTexture;
	sf::Sprite bgSprite, buttonSprite;

public:
	Game();
	void run();
private:
	void processEvent();
	void update();
	void render();
	void startPosition();
	void checkHover();
	void setActive();
	void rollOfDice();
	void playersTurn();
	void movingChips();
};

