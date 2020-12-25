#include "Player.h"

Player::Player(sf::Vector2f position, float speed, sf::Color color) {
	this->player.setPosition(position);
	this->player.setFillColor(color);
	this->player.setSize(sf::Vector2f(20.f, 100.f));
	this->player.setOutlineColor(sf::Color::White);
	this->player.setOutlineThickness(1.f);
	
	this->movementTimerMax = 200.f;
	this->movementTimer = 0.f;
	this->speed = speed;
	this->points = 0;
}

const int Player::getPoints() const
{
	return this->points;
}

const sf::Vector2f Player::getPosition() const
{
	return player.getPosition();
}

void Player::setColor(sf::Color color) {
	this->player.setFillColor(color);
}

void Player::incrementPoints()
{
	++points;
}

void Player::resetPoints()
{
	this->points = 0;
}

void Player::resetMovement()
{
	this->moving = false;
}

void Player::moveUp() {
	this->player.move(0.f, -speed);
	if (this->movementTimer >= this->movementTimerMax) {
		this->moving = true;
		movementTimer = 0.f;
	}
}

void Player::moveDown() {
	this->player.move(0.f, speed);
	if (this->movementTimer >= this->movementTimerMax) {
		this->moving = true;
		movementTimer = 0.f;
	}
}

const bool Player::playerMoved() const
{
	return this->moving;
}

bool Player::checkCollision(Ball& ball)
{
	return this->player.getGlobalBounds().intersects(ball.getGlobalBounds());
}

void Player::updatePlayers()
{
	if (upFlag && player.getPosition().y > 0.f) this->moveUp();
	if (downFlag && player.getPosition().y < 900.f) this->moveDown();
	this->movementTimer += 1.f;
	//std::cout << movementTimer << " ";
}

void Player::renderPlayers(sf::RenderTarget& target)
{
	target.draw(this->player);
}
