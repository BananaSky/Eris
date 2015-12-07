#include "Window.hpp"
#include "ShipSpecs.hpp"
#include "Includes.hpp"
#include "Player.hpp"
#include "ProjectileSpecs.hpp"
#include "Chunk.hpp"
#include "Explosion.hpp"
#include "Wave.hpp"
#include "GuiManager.hpp"
#include "Biome.hpp"

void Window::loadPlanetTexture(std::string textureLocation)
{
	planetTextures.push_back(loadTexture(textureLocation));
	planetTextures.back()->setSmooth(true);
}

void Window::loadAsteroidTexture(std::string textureLocation)
{
	asteroidTextures.push_back(loadTexture(textureLocation));
}

void Window::loadFragmentTexture(std::string textureLocation)
{
	fragTextures.push_back(loadTexture(textureLocation));
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

	auto got = textures.find(textureLocation);
	if (got == textures.end())
	{
		textures.insert(std::pair<std::string, sf::Texture*>(textureLocation, new sf::Texture()));
		if (!textures[textureLocation]->loadFromFile(textureLocation))
		{
			std::cout << "Error Loading Texture" << std::endl;
		}
		
	}
	else
	{
		std::cout << "Already Loaded: " << textureLocation << std::endl;
	}

	textures[textureLocation]->setSmooth(smoothTextures);

	return textures[textureLocation];
}

void Window::loadBackground(std::string location, sf::Vector2f scale = sf::Vector2f(.5f,.5f))
{
	background.setTexture(*loadTexture(location));
	background.setScale(scale);
}

void Window::loadStart(std::string location, sf::Vector2f scale = sf::Vector2f(.5f, .5f))
{
	startScreen.setTexture(*loadTexture(location));
	startScreen.setScale(scale);
}

void Window::loadCrate(std::string location)
{
	crateTexture = *loadTexture(location);
}

void GuiManager::loadFuel(std::string location, sf::Vector2f size = sf::Vector2f(50, 100))
{
	fuel.setTexture(parent->loadTexture(location));
	fuel.setSize(size);
	fuel.setPosition(0, 30);
	parent->getPlayer()->syncFuel(&fuel);
}

void GuiManager::loadHealth(std::string location, sf::Vector2f size = sf::Vector2f(50, 100))
{
	health.setTexture(parent->loadTexture(location));
	health.setSize(size);
	health.setPosition(fuel.getPosition().x + fuel.getSize().x, 30);
	parent->getPlayer()->syncHealth(&health);
}

void GuiManager::loadGUI(std::string location, sf::Vector2f scale = sf::Vector2f(.5f, .5f))
{
	guiBox = *parent->loadTexture(location);
}

void GuiManager::loadInfo(std::string location, sf::Vector2f size = sf::Vector2f(50, 100))
{
	info.setTexture(parent->loadTexture(location));
	info.setSize(size);
	info.setPosition(target->getSize().x - info.getGlobalBounds().width, 0);
}

void GuiManager::loadHide(std::string location, sf::Vector2f scale = sf::Vector2f(1, 1))
{
	hideButton.setTexture(*parent->loadTexture(location));
	hideButton.setScale(scale);
	hideButton.setPosition(target->getSize().x - hideButton.getGlobalBounds().width, info.getSize().y);
}

void GuiManager::loadShow(std::string location, sf::Vector2f scale = sf::Vector2f(1, 1))
{
	showButton.setTexture(*parent->loadTexture(location));
	showButton.setScale(scale);
	showButton.setPosition(target->getSize().x - showButton.getGlobalBounds().width, 0);
}

void Window::loadInv(std::string location, sf::Vector2f size)
{
	player.getInv()->setTexture(loadTexture(location));
	player.getInv()->setSize(size);
	player.getInv()->setPosition(window.getSize().x / 2 - player.getInv()->getLocalBounds().width / 2, 0);
}

void GuiManager::loadMenuBacking(std::string location)
{
	menuBacking = *parent->loadTexture(location);
	stationMenu.setTexture(&menuBacking);
	planetMenu.setTexture(&menuBacking);
}

void GuiManager::loadButtonTexture(std::string location)
{
	buttonTexture = *parent->loadTexture(location);
	stationMenu.loadButtonTexture(&buttonTexture);
	planetMenu.loadButtonTexture(&buttonTexture);
}

void GuiManager::loadSliderButtonTexture(std::string location)
{
	sliderButtonTexture = *parent->loadTexture(location);
	stationMenu.loadSliderButtonTexture(&sliderButtonTexture);
	planetMenu.loadSliderButtonTexture(&sliderButtonTexture);
}

void GuiManager::loadSliderTexture(std::string location)
{
	sliderTexture = *parent->loadTexture(location);
	stationMenu.loadSliderTexture(&sliderTexture);
	planetMenu.loadSliderTexture(&sliderTexture);
}

void GuiManager::loadTextBox(std::string location)
{
	output.setTexture(parent->loadTexture(location));
}

void GuiManager::loadWASD(std::string location)
{
	wasd.setTexture(*parent->loadTexture(location));
}

void GuiManager::loadSPACE(std::string location)
{
	space.setTexture(*parent->loadTexture(location));
}

void Window::loadShipSpecs(std::string filename)
{
	std::ifstream indata;

	indata.open(filename);

	std::string name;
	float shootDelayModifier;
	float engineForce;
	float mass;
	float maxVelocity;
	float maxAngularVelocity;
	float structuralIntegrity;
	float repair;
	std::string texture;
	int cost;
	std::vector<std::string> turretTypes;

	std::string                line;
	std::getline(indata, line);
	while (getline(indata, line)) //For every line of csv, gather the data for each ship type and push it to a map
	{
		turretTypes.clear();

		std::stringstream          lineStream(line);

		//This would be better with some operator overloading, but for now....?

		std::string                cell;
		std::getline(lineStream, name, ',');

		std::getline(lineStream, cell, ',');
		shootDelayModifier = std::stof(cell);

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

		std::getline(lineStream, cell, ',');
		cost = std::stoi(cell);

		while (std::getline(lineStream, cell, ','))
		{
			if (cell != "none")
			{
				turretTypes.push_back(cell);
			}
			else
			{
				break; //Discard the none value
			}
		}

		spec_Keys.push_back(name);
		specs.insert(
			std::pair<std::string, ShipSpecs*>
			(
				name,
				new ShipSpecs
		{
			name,
			shootDelayModifier,
			engineForce,
			mass,
			maxVelocity,
			maxAngularVelocity,
			structuralIntegrity,
			repair,
			texture,
			cost,
			turretTypes
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
			<< "Shoot Delay: " << shootDelayModifier << std::endl
			<< "Engine Force: " << engineForce << std::endl
			<< "Mass: " << mass << std::endl
			<< "Maximum Velocity: " << maxVelocity << std::endl
			<< "Maximum Angular Velocity: " << maxAngularVelocity << std::endl
			<< "Structure: " << structuralIntegrity << std::endl
			<< "Repair Rate: " << repair << std::endl
			<< "Cost" << cost << std::endl;

	}
	std::cout << "\n\n Type Loading Complete.. \n\n" << std::endl;
}

void Window::loadProjectileSpecs(std::string filename)
{
	std::ifstream indata;

	indata.open(filename);

	std::string name;
	int lifetime;
	float damage;
	float acceleration;
	uint8_t accuracy;
	std::string Ammo_Type;
	int basePrice;
	std::string texture;
	std::string itemTexture;

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
		damage = std::stof(cell);

		std::getline(lineStream, cell, ',');
		acceleration = std::stof(cell);

		std::getline(lineStream, cell, ',');
		accuracy = std::stoi(cell);

		std::getline(lineStream, Ammo_Type, ',');

		std::getline(lineStream, cell, ',');
		basePrice = std::stoi(cell);

		std::getline(lineStream, texture, ',');
		std::getline(lineStream, itemTexture, ',');

		p_specs.insert(
			std::pair<std::string, ProjectileSpecs*>
			(
				name,
				new ProjectileSpecs
		{
				lifetime,
				damage,
				acceleration,
				accuracy,
				Ammo_Type,
				texture
		}
				)
			);
		{
			ItemSpecs item{ name, itemTexture, basePrice };

			auto got = itemList.find(name);
			if (got == itemList.end())
			{
				itemList.insert(std::pair<std::string, ItemSpecs>(name, item));
			}
			else
			{
				std::cout << "Already Loaded: " << name << std::endl;
			}
		}

		auto got = textures.find(texture);
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

void Window::loadWaves(std::string filename)
{
	std::ifstream indata;

	indata.open(filename);

	int dispersion;
	std::string type;

	std::string                line;
	std::getline(indata, line); //Skip first line
	while (getline(indata, line))
	{
		Wave currentwave;
		std::vector<std::string> units;

		std::stringstream          lineStream(line);
		std::string                cell;

		std::getline(lineStream, cell, ',');
		dispersion = std::stoi(cell);

		while (std::getline(lineStream, type, ','))
		{
			if (type != "")
			{
				units.push_back(type);
			}
			else
			{
				break;

			}
		}

		waves.push_back(Wave{ dispersion, units });
	}
	std::cout << "\n\n Type Loading Complete.. \n\n" << std::endl;
}

void Window::loadItems(std::string filename)
{
	std::ifstream indata;

	indata.open(filename);

	std::string name;
	std::string texture;
	int basePrice;

	std::string                line;
	std::getline(indata, line);
	while (getline(indata, line)) //For every line of csv, gather the data for each ship type and push it to a map
	{
		std::stringstream          lineStream(line);

		//This would be better with some operator overloading, but for now....?

		std::string                cell;
		std::getline(lineStream, name, ',');
		std::getline(lineStream, texture, ',');

		std::getline(lineStream, cell, ',');
		basePrice = std::stoi(cell);

		ItemSpecs item{ name, texture, basePrice };

		auto got = itemList.find(name);
		if (got == itemList.end())
		{
			itemList.insert(std::pair<std::string, ItemSpecs>(name, item));
		}
		else
		{
			std::cout << "Already Loaded: " << name << std::endl;
		}
	}
	std::cout << "\n\n Type Loading Complete.. \n\n" << std::endl;
}

void Window::loadTurrets(std::string filename)
{
	std::ifstream indata;

	indata.open(filename);

	std::string name;
	std::string ammo_type;
	int baseRate;
	float spreadModifier;
	float accuracyModifier;
	int barrelSpacing;
	int barrels;
	float range;

	std::string                line;
	std::getline(indata, line);
	while (getline(indata, line)) //For every line of csv, gather the data for each ship type and push it to a map
	{
		std::stringstream          lineStream(line);

		//This would be better with some operator overloading, but for now....?

		std::string                cell;
		std::getline(lineStream, name, ',');
		std::getline(lineStream, ammo_type, ',');

		std::getline(lineStream, cell, ',');
		baseRate = std::stoi(cell);

		std::getline(lineStream, cell, ',');
		spreadModifier = std::stof(cell);

		std::getline(lineStream, cell, ',');
		accuracyModifier = std::stof(cell);

		std::getline(lineStream, cell, ',');
		barrelSpacing = std::stoi(cell);

		std::getline(lineStream, cell, ',');
		barrels = std::stoi(cell);

		std::getline(lineStream, cell, ',');
		range = std::stof(cell);

		TurretSpecs turret{ name, ammo_type, baseRate, spreadModifier, accuracyModifier, barrelSpacing, barrels, range };

		auto got = turretSpecs.find(name);
		if (got == turretSpecs.end())
		{
			turretSpecs.insert(std::pair<std::string, TurretSpecs>(name, turret));
		}
		else
		{
			std::cout << "Already Loaded: " << name << std::endl;
		}
	}
	std::cout << "\n\n Type Loading Complete.. \n\n" << std::endl;
}

void Window::loadBiomes(std::string filename)
{
	std::ifstream indata;

	indata.open(filename);

	std::string name;
	int asteroidNum;
	int maxAsteroidRadius;
	int asteroidVelocityMax;

	int maxPlanetNum;
	int maxPlanetRadius;
	int minPlanetRadius;
	int maxStationNumber;
	int closeness;

	int planetChance;
	int stationChance;

	std::string                line;
	std::getline(indata, line);
	while (getline(indata, line)) //For every line of csv, gather the data for each ship type and push it to a map
	{
		std::stringstream          lineStream(line);

		//This would be better with some operator overloading, but for now....?

		std::string                cell;

		std::getline(lineStream, name, ',');

		std::getline(lineStream, cell, ',');
		asteroidNum = std::stoi(cell);

		std::getline(lineStream, cell, ',');
		maxAsteroidRadius = std::stoi(cell);

		std::getline(lineStream, cell, ',');
		asteroidVelocityMax = std::stoi(cell);

		std::getline(lineStream, cell, ',');
		maxPlanetNum = std::stoi(cell);

		std::getline(lineStream, cell, ',');
		maxPlanetRadius = std::stoi(cell);

		std::getline(lineStream, cell, ',');
		minPlanetRadius = std::stoi(cell);

		std::getline(lineStream, cell, ',');
		maxStationNumber = std::stoi(cell);

		std::getline(lineStream, cell, ',');
		closeness = std::stoi(cell);

		std::getline(lineStream, cell, ',');
		planetChance = std::stoi(cell);

		std::getline(lineStream, cell, ',');
		stationChance = std::stoi(cell);

		Biome biome
		{
		asteroidNum,
		maxAsteroidRadius,
		asteroidVelocityMax,
		maxPlanetNum,
		maxPlanetRadius,
		minPlanetRadius,
		maxStationNumber,
		closeness,
		planetChance,
		stationChance 
		};

		auto got = biomes.find(name);
		if (got == biomes.end())
		{
			biomes.insert(std::pair<std::string, Biome>(name, biome));
			std::cout << "Loaded " << name << std::endl;
		}
		else
		{
			std::cout << "Already Loaded: " << name << std::endl;
		}
	}
	std::cout << "\n\n Type Loading Complete.. \n\n" << std::endl;
}

void Window::loadPlayer(sf::Vector2f position, sf::Vector2f scale, std::string name = "Frigate")
{
	player.loadType(*specs[name], this);
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

