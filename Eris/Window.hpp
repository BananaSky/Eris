#pragma once

#include "Includes.hpp"
#include "Ship.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "AI.hpp"
#include "Inventory.hpp"
#include "Fragment.hpp"
#include "Wave.hpp"
#include "GuiManager.hpp"
#include "Crate.hpp"
#include "ItemSpecs.hpp"

class  Chunk;
struct ProjectileSpecs;
struct ShipSpecs;
class  Explosion;
class  Enemy;

class Window
{
public:
	Window();
	Window(std::string title);
	~Window();

	//Some typdefs to make migration to safer memory management also look clean (Limit these)
	typedef std::shared_ptr<Explosion>  explosion_ptr;
	typedef std::shared_ptr<Projectile> projectile_ptr;
	typedef std::shared_ptr<Enemy>	    enemy_ptr;
	typedef std::shared_ptr<AI>         ally_ptr;
	typedef std::shared_ptr<Fragment>   frag_ptr;

	void Init();

	void run();
	void draw();

	void updateCrates();

	void updateEnemies();

	void updateEnemyProjectiles();

	void updateExplosions();

	void updateFragments();

	//All Loading Functions here

	sf::Texture* loadTexture(std::string textureLocation);

	void loadTextureSquare(std::string textureLocation, sf::IntRect rect, std::vector<sf::Texture*>* storeLocation);
	void loadMultiTexture(std::string location, std::vector<sf::Texture*>* storeLocation, int size, int rows, int columns);

	void loadBackground     (std::string location, sf::Vector2f scale);
	void loadStart          (std::string location, sf::Vector2f scale);
	void loadCrate          (std::string location);
	void loadItems(std::string filename);
	void loadPlayer         (sf::Vector2f position, sf::Vector2f scale, std::string name);
	void loadInv            (std::string location, sf::Vector2f size);

	void loadPlanetTexture  (std::string textureLocation);
	void loadAsteroidTexture(std::string textureLocation);
	void loadFragmentTexture(std::string textureLocation);
	void loadStationTexture (std::string textureLocation);

	void loadShipSpecs      (std::string filename);
	void loadProjectileSpecs(std::string filename);
	void loadWaves          (std::string filename);

	//Functions for adding types of projectiles

	//void addExplosion(Explosion* explosion);
	void addFragments(sf::Vector2f position, int amount=40, int spread=1);
	void addCrate(sf::Vector2f position);
	void addProjectile(float rotation, sf::Vector2f position, float velocity, std::string type);
	void addEnemyProjectile(float rotation, sf::Vector2f position, float velocity, std::string type);

	void addExplosion(explosion_ptr explosion);

	//Enemy management

	void spawn(sf::Vector2f position, sf::Vector2f scale, std::string name, bool enemy);
	void spawnWave(const std::vector<std::string>& wave);
	void cycleWave();

	void calcNextWave();

	//Chunks and update

	void genChunks(sf::Vector2f size);

	void buy(std::string index, float percent=.1);
	void sell(std::string index, float percent=.1);

	void updateProjectiles();
	void updateAllies();
	void updatePlayer();
	void updateChunks();
	void update();

	//Screen and GUI managers

	void displayInv();
	void displayStartScreen();
	void displayGameScreen();
	void displayGameOverScreen();

	void addMessage(std::string m) { GUImanager.addMessage(m); }
	void toggleInv()			   { invScreen = !invScreen; player.getInv()->format(&window); pause(); }
	void pause()				   { paused = !paused; }

	//Lots of getters

	std::vector<sf::Texture*>* getAsteroidTextures()               { return &asteroidTextures; }
	std::vector<sf::Texture*>* getPlanetTextures()                 { return &planetTextures; }
	std::vector<sf::Texture*>* getExplosionTextures()              { return &explosionTextures; }
	std::vector<sf::Texture*>* getStationTextures()                { return &stationTextures; }
	std::unordered_map<std::string, sf::Texture*>* getTextures()   { return &textures; }
	std::unordered_map<std::string, ShipSpecs*>* getShipSpecs()    { return &specs; }
	std::unordered_map<std::string, ProjectileSpecs*>* getPSpecs() { return &p_specs; }
	std::vector<std::string>* getSpec_Keys()                       { return &spec_Keys; }
	std::unordered_map<std::string, ItemSpecs>* getItems()              { return &itemList; }

	sf::RenderWindow* getWindow()                                  { return &window; }
	float             getFps()                                     { return fps; }
	Player*           getPlayer()                                  { return &player; }
	sf::View          getNormalView()							   { return view; }
	sf::View          getGUIview()								   { return guiView; }
	Inventory*        getInv()                                     { return player.getInv(); }

	//Score-Related

	int getBalance() { return credits; }
	int getScore()   { return score; }

	void addScore(int n)  { if (n > 0)       { score += n; credits += n; } }
	void spend(int i = 1) { if (credits > i) { credits -= i; } }

public: //Another public declaration to show intent
	GuiManager GUImanager; //Only public temporarily- Will probably change this before the next update

private:

	sf::Sprite background;
	sf::Sprite startScreen;

	sf::RenderWindow window;
	sf::View         view;
	sf::View         guiView;

	float modifier = 1.0;

	float     fps;
	sf::Text  text;
	sf::Font  font;
	sf::Clock clock;
	float     lastTime = 0;

	std::unordered_map<std::string, sf::Texture*> textures;
	std::vector<sf::Texture*>                     planetTextures;
	std::vector<sf::Texture*>                     asteroidTextures;
	std::vector<sf::Texture*>                     explosionTextures;
	std::vector<sf::Texture*>                     stationTextures;
	std::vector<sf::Texture*>                     fragTextures;
	std::vector<std::string>                      spec_Keys;
	sf::Texture                                   crateTexture;

	std::unordered_map<std::string, ShipSpecs*>       specs;
	std::unordered_map<std::string, ProjectileSpecs*> p_specs;

	Player    player;
	int       score;
	int       credits;

	std::unordered_map<int, Chunk> chunks;
	std::vector<Wave>              waves;
	std::vector<frag_ptr>          fragments;
	std::vector<explosion_ptr>     explosions;
	std::vector<projectile_ptr>    projectiles;
	std::vector<projectile_ptr>    enemyProjectiles;
	std::vector<enemy_ptr>         enemies;
	std::vector<ally_ptr>          allies;
	std::vector<Crate>             crates;

	std::unordered_map<std::string, ItemSpecs> itemList;

	static bool smoothTextures;
	static int  textureID;
	static bool gameOver;


	int  counter   = 1;
	int  spawnrate = 100;
	int  wavenum   = 0;
	bool start     = true;
	bool invScreen = false;
	bool paused    = false;
};

