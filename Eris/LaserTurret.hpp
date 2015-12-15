#pragma once
#include "Turret.hpp"

class Window;
struct TurretSpecs;
struct ProjectileSpecs;

class LaserTurret :
	public Turret
{
public:
	LaserTurret();
	~LaserTurret();

	LaserTurret(Ship * parent);

	virtual void shoot(float rotation, sf::Vector2f pos, float velocity, std::string type, Window* board, bool enemy = false);

	float getRange(Window* board);

private:

};

