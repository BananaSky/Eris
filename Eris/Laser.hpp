#pragma once
#include "Projectile.hpp"
#include "LaserTurret.hpp"

class Ship;

class Laser :
	public Projectile
{
public:
	Laser();
	~Laser();

	Laser(float angle, sf::Vector2f pos, float velocity, Ship* parent, Ship* target, bool isEnemy, LaserTurret*);

	virtual void explode(Window * board);

	virtual void draw(sf::RenderWindow* window)
	{
		window->draw(beam);
	}

	void kill() { if (lifetime > 0) { lifetime --; } else { lifetime = 0; } }
	virtual void update(Window * board);

protected:
	LaserTurret* muzzle;

	bool isEnemy;

	Ship* parent;
	Ship* target;

	sf::RectangleShape beam;
};

