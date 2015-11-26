#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "Includes.hpp"
#include "Planet.hpp"

class Board;
class Projectile;

class Asteroid : public Planet
{
public:
	Asteroid();

	void update();

	void setLife(int life) { this->life = life; }

	bool checkCollisionWith(Collidable * collidable);

	void setVelocity(double set) { velocity = set; }

	void applyDamage(int damage) { life -= damage; }

	int getLife() { return life; }

private:
	int life;
	double velocity;
};

#endif