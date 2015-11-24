#pragma once
#include "Collidable.hpp"
class Window;

class Explosion : public Collidable
{

public:
	Explosion(sf::Vector2f, Window* board);

	void update();
	int getLife() { return lifetime; }
	double getDamage() { return damage; }

private:
	double damage = .01;

	std::vector<sf::Texture*>* explosionTextures;
	int explosionRate = 1;
	int currentFrame = 1;
	int lifetime = 0;
};

