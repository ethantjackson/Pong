#include "Game2Player.h"

Game2Player::Game2Player() {
	initVariables();
	initWindow();
	initText();
}

Game2Player::~Game2Player() {
	delete this->window;
	delete this->player1;
	delete this->player2;
	delete this->ball;
}

void Game2Player::checkAllCollisions()
{
	if (this->playerCollisionTimer >= this->playerCollisionTimerMax) {
		if (this->player1->checkCollision(*this->ball) || this->player2->checkCollision(*this->ball)) {
			this->ball->playerCollision();
			this->playerCollisionTimer = 0.f;
		}
	}
	else
		playerCollisionTimer += 1.f;
	//std::cout << playerCollisionTimer;

	if (this->ball->getPosition().x <= 0) {
		this->player2->incrementPoints();
		this->player1->resetMovement();
		this->player2->resetMovement();
	}
	else if (this->ball->getPosition().x >= 1500) {
		this->player1->incrementPoints();
		this->player1->resetMovement();
		this->player2->resetMovement();
	}
	//std::cout << "Player 1: " << this->player1->getPoints() << "  Player2: " << this->player2->getPoints() << std::endl;
}

void Game2Player::initVariables() {
	this->window = nullptr;
	this->playerCollisionTimerMax = 5.f;
	this->playerCollisionTimer = this->playerCollisionTimerMax;
	this->movementTimerMax = 1000.f;
	this->movementTimer = 0.f;
}

void Game2Player::initText()
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

void Game2Player::initWindow() {
	videoMode.height = 1000;
	videoMode.width = 1500;

	this->window = new sf::RenderWindow(this->videoMode, "Pong", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

void Game2Player::pollEvents() {
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
			case sf::Keyboard::R: this->player1->resetPoints(); this->player2->resetPoints(); break;

				// Process the up, down, left and right keys
			case sf::Keyboard::Up:     this->player2->setUpFlag(true); break;
			case sf::Keyboard::Down:    this->player2->setDownFlag(true); break;
			case sf::Keyboard::Left:    this->player2->setDownFlag(true); break;
			case sf::Keyboard::Right:  this->player2->setUpFlag(true); break;

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
			case sf::Keyboard::Up:     this->player2->setUpFlag(false); break;
			case sf::Keyboard::Down:    this->player2->setDownFlag(false); break;
			case sf::Keyboard::Left:    this->player2->setDownFlag(false); break;
			case sf::Keyboard::Right:  this->player2->setUpFlag(false); break;

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

void Game2Player::update() {

	this->pollEvents();

	this->player1->updatePlayers();
	this->player2->updatePlayers();

	if (this->player1->playerMoved() || this->player2->playerMoved()) {
		this->checkAllCollisions();
		this->ball->updateBall();
	}

	this->updateText();
}

void Game2Player::updateText()
{
	std::stringstream ss;
	ss << this->player1->getPoints() << " : " << this->player2->getPoints();
	this->text.setString(ss.str());
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, 0.f);
	text.setPosition(sf::Vector2f(this->window->getSize().x / 2.0f, 10.f));
}

void Game2Player::render() {
	this->window->clear();

	this->player1->renderPlayers(*this->window);
	this->player2->renderPlayers(*this->window);

	this->renderText(*this->window);

	this->ball->renderBall(*this->window);

	this->window->display();
}

void Game2Player::renderText(sf::RenderTarget& target)
{
	target.draw(this->text);
}