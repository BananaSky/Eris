#pragma once

#include "Includes.hpp"
#include "Ship.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "AI.hpp"

class Chunk;
struct ProjectileSpecs;
struct ShipSpecs;
class Explosion;
class Enemy;

class Window
{
public:
	Window();
	Window(std::string title);
	~Window();

	void run();
	sf::Texture* loadTexture(std::string textureLocation);
	void loadBackground(std::string location, sf::Vector2f scale);
	void loadFuel(std::string location, sf::Vector2f scale);
	void loadHealth(std::string location, sf::Vector2f size);
	void loadGUI(std::string location, sf::Vector2f scale);
	void loadAmmo(std::string location, sf::Vector2f size);
	void loadShipSpecs(std::string filename);
	void loadProjectileSpecs(std::string filename);
	void loadPlayer(sf::Vector2f position, sf::Vector2f scale, std::string name);

	void addProjectile(Projectile * projectile, std::string type);
	void addEnemyProjectile(Projectile * projectile, std::string type);
	void spawn(sf::Vector2f position, sf::Vector2f scale, std::string name, bool enemy);
	void addExplosion(Explosion* explosion) { explosions.push_back(explosion); }

	void genChunks(sf::Vector2f size);
	void updateChunks();

	void gui();
	void addBox(sf::Vector2f, sf::Vector2f);

	void loadPlanetTexture(std::string textureLocation);
	void loadAsteroidTexture(std::string textureLocation);
	void loadStationTexture(std::string textureLocation);
	void loadTextureSquare(std::string textureLocation, sf::IntRect rect, std::vector<sf::Texture*>* storeLocation);
	void loadMultiTexture(std::string location, std::vector<sf::Texture*>* storeLocation, int size, int rows, int columns);

	void draw();

	void update();

	std::vector<sf::Texture*>* getAsteroidTextures()  { return &asteroidTextures; }
	std::vector<sf::Texture*>* getPlanetTextures()    { return &planetTextures; }
	std::vector<sf::Texture*>* getExplosionTextures() { return &explosionTextures; }
	std::vector<sf::Texture*>* getStationTextures()   { return &stationTextures; }
	sf::RectangleShape* getFuel() { return &fuel; }

private:

	sf::RenderWindow window;
	sf::View view;
	float modifier = 1.0;
	sf::Sprite background;
	sf::RectangleShape fuel;
	sf::RectangleShape health;
	sf::RectangleShape ammo;
	sf::Texture guiBox;
	std::vector<sf::RectangleShape> guiBoxes;

	float fps;
	sf::Font font;
	sf::Clock clock;
	float lastTime = 0;

	std::unordered_map<std::string, sf::Texture*> textures;
	std::vector<sf::Texture*> planetTextures;
	std::vector<sf::Texture*> asteroidTextures;
	std::vector<sf::Texture*> explosionTextures;
	std::vector<sf::Texture*> stationTextures;
	std::unordered_map<std::string, ShipSpecs*> specs;
	std::unordered_map<std::string, ProjectileSpecs*> p_specs;

	Player player;
	std::vector<AI> allies;
	std::vector<Enemy> enemies;

	std::unordered_map<int, Chunk> chunks;
	std::vector<Explosion*> explosions;
	std::vector<Projectile*> projectiles;
	std::vector<Projectile*> enemyProjectiles;


	static bool smoothTextures;
	static int textureID;
	static bool gameOver;
};

