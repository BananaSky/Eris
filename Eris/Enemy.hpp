#pragma once
#include "AI.hpp"
class Enemy :
	public AI
{
public:
	Enemy();
	~Enemy();
	void shoot(Window * board);
	void update(Window * board, sf::RenderWindow * window);
};

