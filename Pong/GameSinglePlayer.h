#pragma once
#include "Player.h"
class GameSinglePlayer
{
private:
	//window and events
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//text
	sf::Font font;
	sf::Text text;

	//Game Logic
	//Game Logic
	float playerCollisionTimerMax;
	float playerCollisionTimer;
	float movementTimerMax;
	float movementTimer;
	float botMovementTimerMax;
	float botMovementTimer;

	//Game Objects
	sf::Vector2f player1Pos = sf::Vector2f(50.f, 700.f);
	sf::Color player1Color = sf::Color::Red;
	sf::Vector2f botPlayerPos = sf::Vector2f(1430.f, 700.f);
	sf::Color botPlayerColor = sf::Color::Blue;
	Player* player1 = new Player(player1Pos, 15.f, player1Color);
	Player* botPlayer = new Player(botPlayerPos, 10.f, botPlayerColor);
	Ball* ball = new Ball();

	//private functions
	void checkAllCollisions();
	void updateBot();

	//init functions
	void initVariables();
	void initText();
	void initWindow();

public:
	//constructor and destructor
	GameSinglePlayer();
	virtual ~GameSinglePlayer();

	//Accessors
	const bool running() const { return (this->window->isOpen() 
		&& this->player1->getPoints() < 11 && this->botPlayer->getPoints() < 11); }

	void pollEvents();
	void update();
	void updateText();

	void render();
	void renderText(sf::RenderTarget& target);
};


