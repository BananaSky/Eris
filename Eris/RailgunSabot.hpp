#pragma once
#include "Projectile.hpp"
class RailgunSabot :
	public Projectile
{
public:
	RailgunSabot();
	RailgunSabot(float angle, sf::Vector2f pos, float velocity);
	~RailgunSabot();

	void kill() { lifetime -= initialVelocity; }
};

