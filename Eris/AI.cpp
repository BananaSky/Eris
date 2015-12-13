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
	if (target != NULL && target->getDistanceTo(getPosition()) < 100000)
	{
		float angle = getAngleTo(target->getPosition());

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
	float distance = target->getDistanceTo(getPosition());
	if (target != NULL && distance < 100000)
	{
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
	target = board->getNearest(false, getPosition());
	if (target == NULL) //If no enemies
	{
		target = board->getPlayer();
		shooting = false;
		turningLeft = false;
		accelerating = false;
	}
	else
	{
		shooting = true;
	}

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