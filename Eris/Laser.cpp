#include "Laser.hpp"
#include "Ship.hpp"
#include "Window.hpp"

Laser::Laser(){}

Laser::~Laser(){}

Laser::Laser(float angle, sf::Vector2f pos, float velocity, Ship* parent, Ship* target, bool isEnemy, LaserTurret* muzzle)
{
	velocity = velocity;
	setRotation(angle);
	setPosition(pos);
	this->isEnemy = isEnemy;
	this->parent  = parent;
	this->target  = target;
	this->muzzle = muzzle;

	beam.setFillColor(sf::Color::Red);
}

void Laser::update(Window* board)
{
	if (target != NULL)
	{
		float d_x = target->getPosition().x - parent->getPosition().x;
		float d_y = target->getPosition().y - parent->getPosition().y;
		float distance = sqrt(pow(d_x, 2) + pow(d_y, 2));
		if (distance < muzzle->getRange(board))
		{
			float angle = atan2f(d_y, d_x) * 180.0f / 3.1415f;
			if (angle < 0)
			{
				angle = angle + 360;
			}
			setPosition(target->getPosition());
			beam.setPosition(parent->getPosition());
			beam.setRotation(angle);
			beam.setSize(sf::Vector2f(distance, 4));
		}
		else
		{
			setPosition(parent->getPosition());
			beam.setPosition(parent->getPosition());
			beam.setSize(sf::Vector2f(0, 0));
		}
	}
	else
	{
		target = board->getNearest(isEnemy, this->getPosition());
	}

	if (lifetime > 1)
	{
		lifetime--;
	}
	else
	{
		lifetime = 0; //mark for deletion
	}
}
