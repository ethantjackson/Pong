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

#define PI 3.14159265

class Ball
{
private:
	sf::CircleShape ball; 

	float speed;
	bool outOfBounds;
	float dirVectorAngle;
	sf::Vector2f dirVector;

	void move(sf::Vector2f vector);
	void respawn();

	void resetDirVector();

public: 
	Ball();

	sf::FloatRect getGlobalBounds() const;
	const sf::Vector2f getPosition() const;
	void playerCollision();
	void wallCollision();

	void updateBall();
	void renderBall(sf::RenderTarget& target);
};

