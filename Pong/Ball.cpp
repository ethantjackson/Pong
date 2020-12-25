#include "Ball.h"

void Ball::move(sf::Vector2f vector)
{
    this->ball.move(vector);

    if (this->ball.getPosition().x < 0 || this->ball.getPosition().x > 1500 ||
        this->ball.getPosition().y < -10 || this->ball.getPosition().y > 1010) {
        this->outOfBounds = true;
    }
}

void Ball::respawn()
{
    this->ball.setPosition(sf::Vector2f(750.f, 500.f));
    this->outOfBounds = false;
    this->speed = 12.f;

    this->resetDirVector();
}

sf::FloatRect Ball::getGlobalBounds() const
{
    return this->ball.getGlobalBounds();
}

const sf::Vector2f Ball::getPosition() const
{
    return this->ball.getPosition();
}

void Ball::playerCollision()
{   
    speed += 0.5;

    this->dirVectorAngle = (this->dirVectorAngle * -1 - 180) * (1.0 + ((rand() % 200 - 100.0) / 1000.0));
    if (this->dirVectorAngle > 360)
        this->dirVectorAngle -= 360;
    else if (this->dirVectorAngle < -360)
        this->dirVectorAngle += 360;

    //std::cout << dirVectorAngle << std::endl;
    if ((this->dirVectorAngle > 40 && this->dirVectorAngle < 140) || (this->dirVectorAngle > 220 && this->dirVectorAngle < 320))  {
        if (this->dirVectorAngle > 90 && this->dirVectorAngle < 270)
            this->dirVectorAngle *= 1.5;
        else 
            this->dirVectorAngle *= 0.5;
        //std::cout << "ENTERED (positive): " << dirVectorAngle << std::endl;
    }
    if ((this->dirVectorAngle < -40 && this->dirVectorAngle > -140) || (this->dirVectorAngle < -220 && this->dirVectorAngle > -320)) {
        if (this->dirVectorAngle < -90 && this->dirVectorAngle > -270)
            this->dirVectorAngle *= 1.5;
        else
            this->dirVectorAngle *= 0.5;
        //std::cout << "ENTERED (negative): " << dirVectorAngle << std::endl;
    }
    this->dirVector = sf::Vector2f(this->speed * cos(dirVectorAngle * (PI / 180)), this->speed * sin(dirVectorAngle * (PI / 180)));
    this->move(dirVector);
}

void Ball::wallCollision()
{
    this->dirVectorAngle = this->dirVectorAngle * -1;
    this->dirVector = sf::Vector2f(this->speed * cos(dirVectorAngle * (PI / 180)), this->speed * sin(dirVectorAngle * (PI / 180)));
    this->move(dirVector);
}

void Ball::resetDirVector()
{   
    int quadrant = rand() % 4;
    this->dirVectorAngle = rand() % 46;
    
    switch (quadrant) {
    case 0:
        this->dirVectorAngle = this->dirVectorAngle;
    case 1:
        this->dirVectorAngle = this->dirVectorAngle * -1;
    case 2:
        this->dirVectorAngle = this->dirVectorAngle + 180;
    case 3:
        this->dirVectorAngle = (this->dirVectorAngle + 180) * -1;
    }

    this->dirVector = sf::Vector2f(this->speed * cos(dirVectorAngle * (PI / 180)), this->speed * sin(dirVectorAngle * (PI / 180)));
}

Ball::Ball()
{
    this->ball.setRadius(7.5);
    this->ball.setPosition(sf::Vector2f(750.f, 500.f));
    this->ball.setFillColor(sf::Color::White);
    //this->ball.setOutlineColor(sf::Color::Green);
    //this->ball.setOutlineThickness(2.f);
   
    this->outOfBounds = false;
    this->respawn();
}

void Ball::updateBall()
{   
    if (this->ball.getPosition().y <= 10 || this->ball.getPosition().y >= 980) {
        this->wallCollision();
    }

    if (this->outOfBounds)
        this->respawn();
   
    this->move(dirVector);
}

void Ball::renderBall(sf::RenderTarget& target)
{
    target.draw(ball);
}
