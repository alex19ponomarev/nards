#include "Game.h"

Game::Game():
	window(sf::VideoMode(1000, 1000), "NARDS")
{

    if (!bgTexture.loadFromFile("src/bg.jpg")) {
        std::cout << "bg not loaded";
    }
    bgSprite.setTexture(bgTexture);
    if (!buttonTexture.loadFromFile("src/dice.png")) {
        std::cout << "file not loaded";
    }
    buttonSprite.setTexture(buttonTexture);
    buttonSprite.setPosition(sf::Vector2f(450.f, 450.f));

    startPosition();
    
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvent();
        update();
        render();
    }
}

void Game::processEvent()
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::MouseMoved)
            checkHover();
        if (event.type == sf::Event::MouseButtonPressed) {
            setActive();
            if (event.mouseButton.button == sf::Mouse::Left) {
                playersTurn();
            }
        }      
    }
}

void Game::update()
{
}

void Game::render()
{
    window.clear();
    window.draw(bgSprite);
    for (int i = 0; i < 24; i++) {
        for (auto el : field[i]) {
            el.render(window);
        }
    }
    for (int i = 0; i < dices.size(); i++) {
        dices[i].render(window);
    }
    window.draw(buttonSprite);
    window.display();
}

void Game::startPosition()
{
    for (int i = 0; i < 15; i++) {
        Chip chip(sf::Color::Yellow);
        chip.move(0, field[0].size());
        field[0].push_back(chip);
    }

    for (int i = 0; i < 15; i++) {
        Chip chip(sf::Color::Black);
        chip.move(12, field[12].size());
        field[12].push_back(chip);
    }
   
}

void Game::checkHover()
{
    bool flagActiveStatus = false;
    for (int i = 0; i < field->size(); i++) {
        if (field[i].size() > 0 && field[i][field[i].size() - 1].getStatus() == Status::ACTIVE) {
            flagActiveStatus = true;
            break;
        }
    }

    if (flagActiveStatus) {
        for (int i = 0; i < field->size(); i++) {
            if (field[i].size() > 0 && field[i][field[i].size() - 1].getStatus() != Status::ACTIVE) {
                if (event.mouseMove.x >= field[i][field[i].size() - 1].getPosition().x &&
                    event.mouseMove.x <= field[i][field[i].size() - 1].getPosition().x + 44 &&
                    event.mouseMove.y >= field[i][field[i].size() - 1].getPosition().y &&
                    event.mouseMove.y <= field[i][field[i].size() - 1].getPosition().y + 44
                    )
                    field[i][field[i].size() - 1].setStatus(Status::HOVER);
                else {
                    field[i][field[i].size() - 1].setStatus(Status::DEFAULT);
                }
            }
        }
    }
    else {
        for (int i = 0; i < field->size(); i++) {
            if (field[i].size() > 0 && field[i][field[i].size() - 1].getStatus() != Status::ACTIVE) {
                if (event.mouseMove.x >= field[i][field[i].size() - 1].getPosition().x &&
                    event.mouseMove.x <= field[i][field[i].size() - 1].getPosition().x + 44 &&
                    event.mouseMove.y >= field[i][field[i].size() - 1].getPosition().y &&
                    event.mouseMove.y <= field[i][field[i].size() - 1].getPosition().y + 44
                    )
                    field[i][field[i].size() - 1].setStatus(Status::HOVER);
                else {
                    field[i][field[i].size() - 1].setStatus(Status::DEFAULT);
                }
            }
        }
    }
    
}

void Game::setActive()
{
    for (int i = 0; i < field->size(); i++) {
        if (field[i].size() > 0 && field[i][field[i].size() - 1].getStatus() == Status::HOVER) {
            field[i][field[i].size() - 1].setStatus(Status::ACTIVE);
        }
    }
}

void Game::rollOfDice()
{
    int random[2];
    for (int i = 0; i < 2; ++i) {
        random[i] = rand() % (6 - 1 + 1) + 1;
    }
    if (random[0] == random[1]) {
        for (int i = 0; i < 4; i++) {
            Dice cube(random[0]);
            cube.setPosition(i * 40);
            dices.push_back(cube);
        }
    }
    else {
        for (int i = 0; i < 2; i++) {
            Dice cube(random[i]);
            cube.setPosition(i * 40);
            dices.push_back(cube);
        }
    }
}

void Game::playersTurn()
{
    if (dices.size() == 0 && event.mouseButton.x >= buttonSprite.getPosition().x &&
        event.mouseButton.x <= buttonSprite.getPosition().x + 100 &&
        event.mouseButton.y >= buttonSprite.getPosition().y &&
        event.mouseButton.y <= buttonSprite.getPosition().y + 51) {
        rollOfDice();
        buttonSprite.setColor(sf::Color(255, 255, 255, 128));
    }
    else if (dices.size() != 0) movingChips();
}

void Game::movingChips()
{
    int checkNodeNumber = -1;
    for (int i = 0; i < field->size(); i++) {
        if (
            event.mouseButton.x >= Chip::fieldCoord[i].x &&
            event.mouseButton.x <= Chip::fieldCoord[i].x + 44 &&
            event.mouseButton.y >= Chip::fieldCoord[i].y &&
            event.mouseButton.y <= Chip::fieldCoord[i].y + 44
            ) {
            checkNodeNumber = i;
            break;
        }    
    }
    int activeChip=-1;
    for (int i = 0; i < field->size(); i++) {
        if (field[i].size() > 0 && field[i][field[i].size() - 1].getStatus() == Status::ACTIVE) {
            activeChip = i;           
        }
    }
    if (activeChip != -1 && checkNodeNumber!=-1) {
        field[activeChip][field[activeChip].size() - 1].move(activeChip, 2);
    }
}
