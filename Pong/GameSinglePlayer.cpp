#include "GameSinglePlayer.h"

GameSinglePlayer::GameSinglePlayer() {
	initVariables();
	initWindow();
	initText();
}

GameSinglePlayer::~GameSinglePlayer() {
	delete this->window;
	delete this->player1;
	delete this->botPlayer;
	delete this->ball;
}

void GameSinglePlayer::checkAllCollisions()
{
	if (this->playerCollisionTimer >= this->playerCollisionTimerMax) {
		if (this->player1->checkCollision(*this->ball) || this->botPlayer->checkCollision(*this->ball)) {
			this->ball->playerCollision();
			this->playerCollisionTimer = 0.f;
		}
	}
	else
		playerCollisionTimer += 1.f;
	//std::cout << playerCollisionTimer;

	if (this->ball->getPosition().x <= 0) {
		this->botPlayer->incrementPoints();
		this->player1->resetMovement();
		this->botPlayer->resetMovement();
	}
	else if (this->ball->getPosition().x >= 1500) {
		this->player1->incrementPoints();
		this->player1->resetMovement();
		this->botPlayer->resetMovement();
	}
	//std::cout << "Player 1: " << this->player1->getPoints() << "  botPlayer: " << this->botPlayer->getPoints() << std::endl;
}

void GameSinglePlayer::initVariables() {
	this->window = nullptr;
	this->playerCollisionTimerMax = 15.f;
	this->playerCollisionTimer = this->playerCollisionTimerMax;
	this->movementTimerMax = 50.f;
	this->movementTimer = 0.f;
	this->botMovementTimerMax = 5.f;
	this->botMovementTimer = 4.f;
}

void GameSinglePlayer::initText()
{
	if (!this->font.loadFromFile("res/sansation.ttf")) {
		std::cout << "error loading file \n";
		system("pause");
	}
	this->text.setFont(this->font);
	this->text.setPosition(sf::Vector2f(0.f, 0.f));
	this->text.setCharacterSize(100);
	this->text.setFillColor(sf::Color::Black);
	this->text.setOutlineColor(sf::Color::White);
	this->text.setOutlineThickness(5.f);
	this->text.setStyle(sf::Text::Bold);
	this->text.setString("NONE");
}

void GameSinglePlayer::initWindow() {
	videoMode.height = 1000;
	videoMode.width = 1500;

	this->window = new sf::RenderWindow(this->videoMode, "Pong", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

void GameSinglePlayer::pollEvents() {
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;

			// If a key is pressed
		case sf::Event::KeyPressed:
			switch (this->ev.key.code) {
				// If escape is pressed, close the application
			case  sf::Keyboard::Escape: this->window->close(); break;

				// If enter is R is pressed, reset points
			case sf::Keyboard::R: this->player1->resetPoints(); this->botPlayer->resetPoints(); break;

				// Process the up, down, left and right keys
			case sf::Keyboard::Up:     this->player1->setUpFlag(true); break;
			case sf::Keyboard::Down:    this->player1->setDownFlag(true); break;
			case sf::Keyboard::Left:    this->player1->setDownFlag(true); break;
			case sf::Keyboard::Right:  this->player1->setUpFlag(true); break;
			

			case sf::Keyboard::W:   this->player1->setUpFlag(true); break;
			case sf::Keyboard::S:	this->player1->setDownFlag(true); break;
			case sf::Keyboard::D:   this->player1->setDownFlag(true); break;
			case sf::Keyboard::A:   this->player1->setUpFlag(true); break;

			default: break;
			}
			break;

			// If a key is released
		case sf::Event::KeyReleased:
			switch (ev.key.code)
			{
				// Process the up, down, left and right keys
			
			case sf::Keyboard::Up:     this->player1->setUpFlag(false); break;
			case sf::Keyboard::Down:    this->player1->setDownFlag(false); break;
			case sf::Keyboard::Left:    this->player1->setDownFlag(false); break;
			case sf::Keyboard::Right:  this->player1->setUpFlag(false); break;
			

			case sf::Keyboard::W:  this->player1->setUpFlag(false); break;
			case sf::Keyboard::S:  this->player1->setDownFlag(false); break;
			case sf::Keyboard::D:  this->player1->setDownFlag(false); break;
			case sf::Keyboard::A:  this->player1->setUpFlag(false); break;
			}
			break;
		default: break;
		}
	}
}

void GameSinglePlayer::update() {

	this->pollEvents();

	this->player1->updatePlayers();
	if (this->botMovementTimer >= this->botMovementTimerMax) {
		this->updateBot();
		this->botMovementTimer = 0.f;
	}
	else {
		this->botPlayer->updatePlayers();
		this->botMovementTimer += 1.f;
	}
	
	if (this->player1->playerMoved()) {
		this->checkAllCollisions();
		this->ball->updateBall();
	}
	

	this->updateText();
}

void GameSinglePlayer::updateBot()
{
	this->botPlayer->setDownFlag(false);
	this->botPlayer->setUpFlag(false);
	if ((this->botPlayer->getPosition().y + 95.f) < this->ball->getPosition().y) {
		//std::cout << "bot above target" << std::endl;
		this->botPlayer->setDownFlag(true);
	}
	else if ((this->botPlayer->getPosition().y + 5.f) > this->ball->getPosition().y) {
		//std::cout << "bot below target" << std::endl;
		this->botPlayer->setUpFlag(true);
	}
	this->botPlayer->updatePlayers();
}

void GameSinglePlayer::updateText()
{
	std::stringstream ss;
	ss << this->player1->getPoints() << " : " << this->botPlayer->getPoints();
	this->text.setString(ss.str());
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, 0.f);
	text.setPosition(sf::Vector2f(this->window->getSize().x / 2.0f, 10.f));
}

void GameSinglePlayer::render() {
	this->window->clear();

	this->player1->renderPlayers(*this->window);
	this->botPlayer->renderPlayers(*this->window);

	this->renderText(*this->window);

	this->ball->renderBall(*this->window);

	this->window->display();
}

void GameSinglePlayer::renderText(sf::RenderTarget& target)
{
	target.draw(this->text);
}