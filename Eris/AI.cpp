#include "AI.hpp"
#include "Ship.hpp"
#include "Window.hpp"
#include "ProjectileSpecs.hpp"

AI::AI() { this->shooting = true; selectedType = 0; }
AI::~AI(){}

AI::AI(Ship* target)
{
	this->target = target;
	this->shooting = true;
}

void AI::turnTo() 
{
	if (target != NULL)
	{
		float d_x = target->getPosition().x - getPosition().x;
		float d_y = target->getPosition().y - getPosition().y;
		float angle = atan2f(d_y, d_x) * 180 / 3.1415;

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
	if (keepAtRange)
	{
		followDistance = (int)board->getPSpecs()->at(missleTypes[selectedType])->calcRange(velocity);
	}
	turnTo();
	forward();
	Ship::update(board, window);
}