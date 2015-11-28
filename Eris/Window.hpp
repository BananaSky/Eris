#pragma once

#include "Includes.hpp"
#include "Ship.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "AI.hpp"
#include "Inventory.hpp"
#include "Wave.hpp"

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
	void loadStart(std::string location, sf::Vector2f scale);
	void loadFuel(std::string location, sf::Vector2f scale);
	void loadHealth(std::string location, sf::Vector2f size);
	void loadGUI(std::string location, sf::Vector2f scale);
	void loadAmmo(std::string location, sf::Vector2f size);
	void loadInfo(std::string location, sf::Vector2f size);

	void loadHide(std::string location, sf::Vector2f size);

	void loadShow(std::string location, sf::Vector2f size);

	void loadInv(std::string location, sf::Vector2f size);

	void loadShipSpecs(std::string filename);
	void loadProjectileSpecs(std::string filename);
	void loadWaves(std::string filename);
	void loadPlayer(sf::Vector2f position, sf::Vector2f scale, std::string name);

	void addProjectile(Projectile * projectile, std::string type);
	void addEnemyProjectile(Projectile * projectile, std::string type);
	void spawn(sf::Vector2f position, sf::Vector2f scale, std::string name, bool enemy);
	void spawnWave(const std::vector<std::string>& wave);
	void cycleWave();
	void addExplosion(Explosion* explosion) { explosions.push_back(explosion); }

	void genChunks(sf::Vector2f size);
	void updateChunks();

	void stationGUI();

	void DrawCascadingText(std::string output, int offset);

	void InfoGUI();

	void gui();
	void addBox(sf::Vector2f, sf::Vector2f);

	void loadPlanetTexture(std::string textureLocation);
	void loadAsteroidTexture(std::string textureLocation);
	void loadStationTexture(std::string textureLocation);
	void loadTextureSquare(std::string textureLocation, sf::IntRect rect, std::vector<sf::Texture*>* storeLocation);
	void loadMultiTexture(std::string location, std::vector<sf::Texture*>* storeLocation, int size, int rows, int columns);

	void draw();

	void updateProjectiles();

	void updateShips();

	void update();

	void displayInv();

	void displayStartScreen();
	void displayGameScreen();
	void displayGameOverScreen();

	std::vector<sf::Texture*>* getAsteroidTextures()  { return &asteroidTextures; }
	std::vector<sf::Texture*>* getPlanetTextures()    { return &planetTextures; }
	std::vector<sf::Texture*>* getExplosionTextures() { return &explosionTextures; }
	std::vector<sf::Texture*>* getStationTextures()   { return &stationTextures; }
	std::unordered_map<std::string, sf::Texture*>* getTextures() { return &textures; }
	sf::RectangleShape* getFuel() { return &fuel; }


	void addScore(int n) { score += n; credits += n; }
	void spend(int i = 1) { credits -= i; }
	int getBalance() { return credits; }

	bool isNearStation() { return nearStation; }

	std::unordered_map<std::string, ShipSpecs*>* getShipSpecs() { return &specs; }
	std::unordered_map<std::string, ProjectileSpecs*>* getPSpecs() { return &p_specs; }
	std::vector<std::string>* getSpec_Keys() { return &spec_Keys; }

	sf::RenderWindow* getWindow() { return &window; }

	void toggleInv() { invScreen = !invScreen; }

private:
	bool nearStation;

	sf::RenderWindow window;
	sf::View view;
	float modifier = 1.0;
	sf::Sprite background;
	sf::RectangleShape fuel;
	sf::RectangleShape health;
	sf::RectangleShape ammo;
	sf::Texture guiBox;
	std::vector<sf::RectangleShape> guiBoxes;
	sf::Sprite startScreen;
	sf::RectangleShape info;
	sf::Sprite hideButton;
	sf::Sprite showButton;

	float fps;
	sf::Text text;
	sf::Font font;
	sf::Clock clock;
	float lastTime = 0;

	std::unordered_map<std::string, sf::Texture*> textures;
	std::vector<sf::Texture*> planetTextures;
	std::vector<sf::Texture*> asteroidTextures;
	std::vector<sf::Texture*> explosionTextures;
	std::vector<sf::Texture*> stationTextures;

	std::vector<std::string> spec_Keys;

	std::unordered_map<std::string, ShipSpecs*> specs;
	std::unordered_map<std::string, ProjectileSpecs*> p_specs;

	Player player;
	int score;
	int credits;
	Inventory inventory;

	std::unordered_map<int, Chunk> chunks;
	std::vector<Explosion*> explosions;
	std::vector<Enemy> enemies;
	std::vector<AI> allies;
	std::vector<Projectile*> projectiles;
	std::vector<Projectile*> enemyProjectiles;

	std::vector<Wave> waves;

	static bool smoothTextures;
	static int textureID;
	static bool gameOver;

	int counter = 1;
	int spawnrate = 100;
	int wavenum = 0;

	bool start = true;
	bool infoHidden;
	bool invScreen;
};

