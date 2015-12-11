#pragma once
#include "Turret.hpp"
class SmartMissleLauncher :
	public Turret
{
public:
	SmartMissleLauncher();
	~SmartMissleLauncher();
	SmartMissleLauncher(Ship * parent);
	void shoot(float rotation, sf::Vector2f pos, float velocity, std::string type, Window * board, bool enemy);
};

