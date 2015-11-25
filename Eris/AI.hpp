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

	void update(Window*, sf::RenderWindow*);

private:
	Ship* target;
	float angleRange = 30;
	float followDistance = 200;

};

