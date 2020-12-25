#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <sstream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include "Ball.h"

class Player
{
private:
	sf::RectangleShape player; 
	bool upFlag = false;
	bool downFlag = false;
	bool moving = false;
	float movementTimerMax;
	float movementTimer;

	float speed;
	int points;

public: 
	Player(sf::Vector2f position, float speed, sf::Color color);
	
	//accesssors
	const int getPoints() const;
	const sf::Vector2f getPosition() const;
	const bool playerMoved() const;

	//modifiers
	void setColor(sf::Color color);
	void setUpFlag(bool flagState) {
		upFlag = flagState;
	}
	void setDownFlag(bool flagState) {
		downFlag = flagState;
	}
	void incrementPoints();
	void resetPoints();
	void resetMovement();
	
	//movement
	void moveUp();
	void moveDown();
	
	bool checkCollision(Ball& ball);
	void updatePlayers();
	void renderPlayers(sf::RenderTarget& target);
};

