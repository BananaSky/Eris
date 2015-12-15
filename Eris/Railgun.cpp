#include "Railgun.hpp"
#include "Window.hpp"
#include "ProjectileSpecs.hpp"
#include "Ship.hpp"
#include "RailgunSabot.hpp"

Railgun::Railgun(){}

Railgun::~Railgun(){}

Railgun::Railgun(Ship* parent) { this->parent = parent; }

void Railgun::shoot(float rotation, sf::Vector2f pos, float velocity, std::string type, Window* board, bool enemy)
{
	ProjectileSpecs* current_specs = board->getPSpecs()->at(type);

	std::vector<projectile_ptr>* projectiles; //Could use auto, but type needs to be deduced and this needs to be declared before the if statement

	if (!enemy)
	{
		projectiles = board->getProjectiles();
	}
	else
	{
		projectiles = board->getEnemyProjectiles();
	}

	if (fixed)
	{
		for (int i = 0; i < barrels; i++)
		{
			pos.x += ((float)(rand() % (2 * 3) - 3)) * spreadModifier
				+ (float)barrelPositions[i].x * cosf(rotation)
				+ (float)barrelPositions[i].y * sinf(rotation);

			pos.y += ((float)(rand() % (2 * 3) - 3)) * spreadModifier
				+ (float)barrelPositions[i].x * sinf(rotation)
				+ (float)barrelPositions[i].y * cosf(rotation);

			float angle = rotation + ((float)((rand() % 2 * (100 - current_specs->accuracy) - (100 - current_specs->accuracy)) / 100)) * accuracyModfier;

			velocity += rand() % 4 - 1;

			projectiles->push_back(projectile_ptr(new RailgunSabot(angle, pos, velocity)));
			projectiles->back()->setTexture(*board->getTextures()->at(current_specs->texture));
			projectiles->back()->loadType(board->getPSpecs()->at(type));
		}
	}
	else
	{
		Ship* target;
		target = board->getNearest(enemy, parent->getPosition());

		if (target != NULL && target->getDistanceTo(parent->getPosition()) < range)
		{
			for (int i = 0; i < barrels; i++)
			{
				pos.x += ((float)(rand() % (2 * 3) - 3)) * spreadModifier
					+ (float)barrelPositions[i].x * cosf(rotation)
					+ (float)barrelPositions[i].y * sinf(rotation);

				pos.y += ((float)(rand() % (2 * 3) - 3)) * spreadModifier
					+ (float)barrelPositions[i].x * sinf(rotation)
					+ (float)barrelPositions[i].y * cosf(rotation);

				float angle = parent->getAngleTo(target->getPosition());

				velocity += rand() % 4 - 1;

				projectiles->push_back(projectile_ptr(new RailgunSabot(angle, pos, velocity)));
				projectiles->back()->setTexture(*board->getTextures()->at(current_specs->texture));
				projectiles->back()->loadType(board->getPSpecs()->at(type));
			}
		}
		else
		{
			for (int i = 0; i < barrels; i++)
			{
				pos.x += ((float)(rand() % (2 * 3) - 3)) * spreadModifier
					+ (float)barrelPositions[i].x * cosf(rotation)
					+ (float)barrelPositions[i].y * sinf(rotation);

				pos.y += ((float)(rand() % (2 * 3) - 3)) * spreadModifier
					+ (float)barrelPositions[i].x * sinf(rotation)
					+ (float)barrelPositions[i].y * cosf(rotation);

				float angle = rotation + ((float)((rand() % 2 * (100 - current_specs->accuracy) - (100 - current_specs->accuracy)) / 100)) * accuracyModfier;

				velocity += rand() % 4 - 1;

				projectiles->push_back(projectile_ptr(new RailgunSabot(angle, pos, velocity)));
				projectiles->back()->setTexture(*board->getTextures()->at(current_specs->texture));
				projectiles->back()->loadType(board->getPSpecs()->at(type));
			}
		}
	}
}