#pragma once
#include "Includes.hpp"

struct TurretSpecs
{
	std::string name;
	std::string ammo_type;
	int baseRate;
	float spreadModifier;
	float accuracyModifier;

	int barrelSpacing;
	int barrels;
};