#include "Window.hpp"
#include "ShipSpecs.hpp"
#include "Includes.hpp"
#include "Player.hpp"
#include "ProjectileSpecs.hpp"
#include "Chunk.hpp"
#include "Explosion.hpp"

void Window::loadPlanetTexture(std::string textureLocation)
{
	planetTextures.push_back(loadTexture(textureLocation));
	planetTextures.back()->setSmooth(true);
}

void Window::loadAsteroidTexture(std::string textureLocation)
{
	asteroidTextures.push_back(loadTexture(textureLocation));
}

void Window::loadStationTexture(std::string textureLocation)
{
	stationTextures.push_back(loadTexture(textureLocation));
	stationTextures.back()->setSmooth(true);
}

void Window::loadTextureSquare(std::string textureLocation, sf::IntRect rect, std::vector<sf::Texture*>* storeLocation)
{
	storeLocation->push_back(new sf::Texture);
	//Allocate and load a new texture into memory

	if (!storeLocation->back()->loadFromFile(textureLocation, rect))
	{
		std::cout << "Error Loading Texture" << std::endl;
	}
	storeLocation->back()->setSmooth(smoothTextures);
}

void Window::loadMultiTexture(std::string location, std::vector<sf::Texture*>* storeLocation, int size = 64, int rows = 1, int columns = 1)
{
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			loadTextureSquare(location, sf::IntRect(j*size, i*size, size, size), storeLocation);
		}
	}
}


sf::Texture* Window::loadTexture(std::string textureLocation)
{
	//This is to keep track of our textures, and ensure they are freed when we delete the gameboard
	textureID++;

	textures.insert(std::pair<std::string, sf::Texture*>(std::to_string(textureID), new sf::Texture));
	//Allocate and load a new texture into memory

	if (!textures[std::to_string(textureID)]->loadFromFile(textureLocation))
	{
		std::cout << "Error Loading Texture" << std::endl;
	}

	textures[std::to_string(textureID)]->setSmooth(smoothTextures);

	return textures[std::to_string(textureID)];
}

void Window::loadBackground(std::string location, sf::Vector2f scale = sf::Vector2f(.5f,.5f))
{
	background.setTexture(*loadTexture(location));
	background.setScale(scale);
}

void Window::loadFuel(std::string location, sf::Vector2f size = sf::Vector2f(50, 100))
{
	fuel.setTexture(loadTexture(location));
	fuel.setSize(size);
	fuel.setPosition(0, 30);
	player.syncFuel(&fuel);
}

void Window::loadHealth(std::string location, sf::Vector2f size = sf::Vector2f(50, 100))
{
	health.setTexture(loadTexture(location));
	health.setSize(size);
	health.setPosition(fuel.getPosition().x + fuel.getSize().x, 30);
	player.syncHealth(&health);
}

void Window::loadGUI(std::string location, sf::Vector2f scale = sf::Vector2f(.5f, .5f))
{
	guiBox = *loadTexture(location);
}

void Window::loadAmmo(std::string location, sf::Vector2f size = sf::Vector2f(50, 100))
{
	ammo.setTexture(loadTexture(location));
	ammo.setSize(size);
	ammo.setPosition(0, 330);
	player.syncAmmo(&ammo);
}

void Window::loadShipSpecs(std::string filename)
{
	std::ifstream indata;

	indata.open(filename);

	std::string name;
	int shootDelay;
	float engineForce;
	float mass;
	float maxVelocity;
	float maxAngularVelocity;
	float structuralIntegrity;
	float repair;
	std::string texture;

	std::string missleType;

	std::string                line;
	std::getline(indata, line);
	while (getline(indata, line))
	{
		std::stringstream          lineStream(line);

		//This would be better with some operator overloading, but for now....?

		std::string                cell;
		std::getline(lineStream, name, ',');

		std::getline(lineStream, cell, ',');
		shootDelay = std::stoi(cell);

		std::getline(lineStream, cell, ',');
		engineForce = std::stof(cell);

		std::getline(lineStream, cell, ',');
		mass = std::stof(cell);

		std::getline(lineStream, cell, ',');
		maxVelocity = std::stof(cell);

		std::getline(lineStream, cell, ',');
		maxAngularVelocity = std::stof(cell);

		std::getline(lineStream, cell, ',');
		structuralIntegrity = std::stof(cell);

		std::getline(lineStream, cell, ',');
		repair = std::stof(cell);

		std::getline(lineStream, texture, ',');

		std::getline(lineStream, missleType, ',');

		specs.insert(
			std::pair<std::string, ShipSpecs*>
			(
				name,
				new ShipSpecs
		{
			shootDelay,
			engineForce,
				mass,
				maxVelocity,
				maxAngularVelocity,
				structuralIntegrity,
				repair,
				texture,
				missleType
		}
				)
			);

		std::unordered_map<std::string, sf::Texture*>::const_iterator got = textures.find(texture);
		if (got == textures.end())
		{
			textures.insert(std::pair<std::string, sf::Texture*>(texture, new sf::Texture()));
			if (!textures[texture]->loadFromFile(texture))
			{
				std::cout << "Error Loading Texture" << std::endl;
			}
		}
		else
		{
			std::cout << "Already Loaded: " << texture << std::endl;
		}

		std::cout << name << ": " << std::endl
			<< "Shoot Delay: " << shootDelay << std::endl
			<< "Engine Force: " << engineForce << std::endl
			<< "Mass: " << mass << std::endl
			<< "Maximum Velocity: " << maxVelocity << std::endl
			<< "Maximum Angular Velocity: " << maxAngularVelocity << std::endl
			<< "Structure: " << structuralIntegrity << std::endl
			<< "Repair Rate: \n" << repair << std::endl;

	}
	std::cout << "\n\n Type Loading Complete.. \n\n" << std::endl;
}

void Window::loadProjectileSpecs(std::string filename)
{
	std::ifstream indata;

	indata.open(filename);

	std::string name;
	int lifetime;
	float hitRadius;
	float damage;
	float maxVelocity;
	float acceleration;
	std::string texture;

	std::string                line;
	std::getline(indata, line);
	while (getline(indata, line))
	{
		std::stringstream          lineStream(line);

		//This would be better with some operator overloading, but for now....?

		std::string                cell;
		std::getline(lineStream, name, ',');

		std::getline(lineStream, cell, ',');
		lifetime = std::stoi(cell);

		std::getline(lineStream, cell, ',');
		hitRadius = std::stof(cell);

		std::getline(lineStream, cell, ',');
		damage = std::stof(cell);

		std::getline(lineStream, cell, ',');
		maxVelocity = std::stof(cell);

		std::getline(lineStream, cell, ',');
		acceleration = std::stof(cell);

		std::getline(lineStream, texture, ',');

		p_specs.insert(
			std::pair<std::string, ProjectileSpecs*>
			(
				name,
				new ProjectileSpecs
		{
			lifetime,
			hitRadius,
				damage,
				maxVelocity,
				acceleration,
				texture
		}
				)
			);

		std::unordered_map<std::string, sf::Texture*>::const_iterator got = textures.find(texture);
		if (got == textures.end())
		{
			textures.insert(std::pair<std::string, sf::Texture*>(texture, new sf::Texture()));
			if (!textures[texture]->loadFromFile(texture))
			{
				std::cout << "Error Loading Texture" << std::endl;
			}
		}
		else
		{
			std::cout << "Already Loaded: " << texture << std::endl;
		}
		std::cout << "Loaded " << name << std::endl;

	}
	std::cout << "\n\n Type Loading Complete.. \n\n" << std::endl;
}

void Window::loadPlayer(sf::Vector2f position, sf::Vector2f scale, std::string name = "Frigate")
{
	player.loadType(*specs[name]);
	std::unordered_map<std::string, sf::Texture*>::const_iterator got = textures.find(specs[name]->texture);
	if (got == textures.end())
	{
		std::cout << "ALERT: " << specs[name]->texture << "Not found... " << std::endl;
	}
	else
	{
		player.setTexture(*textures[specs[name]->texture]);
	}
	player.setPosition(position);
	player.scale(scale);
	player.setOrigin(player.getLocalBounds().width / 2, player.getLocalBounds().height / 2);
}

void Window::loadStartScreen(std::string location, sf::Vector2f scale)
{
	startScreen.setTexture(*loadTexture(location));
	startScreen.setScale(scale);
}