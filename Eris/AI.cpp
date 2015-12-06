#include "AI.hpp"
#include "Ship.hpp"
#include "Window.hpp"
#include "ProjectileSpecs.hpp"

AI::AI() { this->shooting = true; selectedAmmoType = 0; health.setFillColor(sf::Color::Green); }
AI::~AI(){}

AI::AI(Ship* target)
{
	this->target = target;
	this->shooting = true;
	health.setFillColor(sf::Color::Green);
}

void AI::turnTo() 
{
	if (target != NULL)
	{
		float d_x = target->getPosition().x - getPosition().x;
		float d_y = target->getPosition().y - getPosition().y;
		float angle = atan2f(d_y, d_x) * 180.0f / 3.1415f;

		if (angle < 0)
		{
			angle = angle + 360;
		}
		float d_angle = getRotation() - angle;

		if (abs(d_angle) < angleRange)
		{
			setRotation(angle);
		}
		else
		{
			if (getRotation() > angle)
			{
				turningLeft = true;
				turningRight = false;
			}
			else
			{
				turningRight = true;
				turningLeft = false;
			}
		}
	}
}

void AI::forward()
{
	if (target != NULL)
	{
		float d_x = target->getPosition().x - getPosition().x;
		float d_y = target->getPosition().y - getPosition().y;
		float distance = sqrt(abs(d_x * d_x + d_y *d_y));
		if (distance > followDistance)
		{
			accelerating = true;
			decelerating = false;
		}
		else
		{
			accelerating = false;
			if (keepAtRange)
			{
				decelerating = true;
			}
			else
			{
				if (getVelocity() > 0)
				{
					decelerating = true;
				}
				else
				{
					decelerating = false;
				}
			}
		}
	}
}

void AI::update(Window* board, sf::RenderWindow* window)
{
	health.setPosition(this->getPosition().x - health.getSize().x / 2, this->getPosition().y - 30);
	health.setSize(sf::Vector2f(structuralIntegrity, 8));

	if (structuralIntegrity < maxIntegrity / 2)
	{
		health.setFillColor(sf::Color::Yellow);
	}
	else if (structuralIntegrity < maxIntegrity / 3)
	{
		health.setFillColor(sf::Color::Red);
	}

	if (keepAtRange)
	{
		followDistance = board->getPSpecs()->at(ammoTypes[selectedAmmoType])->calcRange(velocity);
	}
	turnTo();
	forward();
	Ship::update(board, window);
}