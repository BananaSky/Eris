#pragma once
#include "Ship.hpp"
class AI :
	public Ship
{
public:
	AI();
	~AI();

	AI(Ship * target);

	void turnTo();

	void forward(float d_x, float d_y);

	void setTarget(Ship* t) { target = t; followDistance = sqrt(pow(target->getLocalBounds().height, 2) + pow(target->getLocalBounds().width, 2)); }

	virtual void update(Window*, sf::RenderWindow*);

	virtual void shoot(Window* board) { Ship::shoot(board); }

private:
	Ship* target;
	float angleRange = 30;
	float followDistance = 200;

};

