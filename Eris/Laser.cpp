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

void Laser::explode(Window* board)
{
	//Do nothing :)
}

void Laser::update(Window* board)
{
	if (target != NULL)
	{
		float distance = getDistanceTo(target->getPosition());
		if (parent->getStructure() > 0)
		{
			if (distance < muzzle->getRange(board))
			{
				float angle = getAngleTo(target->getPosition());

				setPosition(target->getPosition());
				beam.setPosition(parent->getPosition());
				beam.setRotation(angle);
				beam.setSize(sf::Vector2f(distance, 4));
			}
		}
		else
		{
			setPosition(parent->getPosition());
			beam.setPosition(parent->getPosition());
			beam.setSize(sf::Vector2f(0, 0));
			lifetime = 0;
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
