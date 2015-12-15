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

	void forward();

	void setTarget(Ship* t) { target = t; followDistance = sqrt(pow(target->getLocalBounds().height, 2) + pow(target->getLocalBounds().width, 2)); }

	virtual void update(Window*, sf::RenderWindow*);

	virtual void shoot(Window* board) { Ship::shoot(board); }

	virtual void applyDamage(float damage) { structuralIntegrity -= damage; }

	void drawHealth(sf::RenderWindow* window) { window->draw(health); }

protected:
	bool keepAtRange = true;

	Ship* target;
	float angleRange = 30;
	float followDistance = 200;

	sf::RectangleShape health;
};

