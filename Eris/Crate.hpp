#pragma once
#include "Includes.hpp"
#include "Inventory.hpp"
#include "Item.hpp"

class Crate :
	public Inventory
{
public:
	Crate();
	~Crate();

	float rarity;
};

