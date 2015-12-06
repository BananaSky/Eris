#pragma once
#include "Includes.hpp"
#include "Projectile.hpp"

class Window;
struct TurretSpecs;

class Turret
{
public:
	Turret();
	~Turret();

	void loadType(TurretSpecs type);

	void findBarrelPositions(int n);

	typedef std::shared_ptr<Projectile> projectile_ptr;

	void shoot(float rotation, sf::Vector2f pos, float velocity, std::string type, Window* board, bool enemy=false);

	std::string getName() { return name; }
	std::string getAmmoType() { return ammo_type; }
	int getBaseRate() { return baseRate; }
	int getBarrels() { return barrels; }

private:
	int baseRate;

	float spreadModifier  = 1.0;
	float accuracyModfier = 10.0;

	std::string name;
	std::string ammo_type;

	int barrelSpacing;
	int barrels;

	std::vector<sf::Vector2f> barrelPositions;
};

