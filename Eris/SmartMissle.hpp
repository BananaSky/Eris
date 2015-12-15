#pragma once
#include "Projectile.hpp"
#include "Laser.hpp"

class SmartMissle :
	public Laser
{
public:
	SmartMissle();
	~SmartMissle();
	SmartMissle(float angle, sf::Vector2f pos, float velocity, Ship * parent, Ship * target, bool isEnemy);

	virtual void draw(sf::RenderWindow* window)
	{
		window->draw(*this);
	}

	virtual void kill() { lifetime = 0; }

	void explode(Window * board);

	void update(Window * board);

private:

	float lastDistance = 1.0E10f;
};