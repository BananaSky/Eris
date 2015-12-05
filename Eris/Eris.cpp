#include "Includes.hpp"
#include "Window.hpp"

//https://solarianprogrammer.com/2012/07/18/perlin-noise-cpp-11/
//http://devmag.org.za/2009/04/25/perlin-noise/

int main(int argc, char** argv)
{
	std::cout << "Eris.." << std::endl;

	Window gamewindow("Eris");

	gamewindow.loadMultiTexture("Graphics/Projectiles/ExplosionHD.png", gamewindow.getExplosionTextures(), 256, 4, 4);

	gamewindow.loadAsteroidTexture("Graphics/Asteroids/Asteroid_1.png");
	gamewindow.loadAsteroidTexture("Graphics/Asteroids/Asteroid_2.png");
	gamewindow.loadAsteroidTexture("Graphics/Asteroids/Asteroid_3.png");
	gamewindow.loadAsteroidTexture("Graphics/Asteroids/Asteroid_4.png");
	gamewindow.loadAsteroidTexture("Graphics/Asteroids/Asteroid_5.png");
	gamewindow.loadAsteroidTexture("Graphics/Asteroids/Asteroid_6.png");
	gamewindow.loadAsteroidTexture("Graphics/Asteroids/Asteroid_7.png");
	gamewindow.loadAsteroidTexture("Graphics/Asteroids/Asteroid_8.png");
	gamewindow.loadAsteroidTexture("Graphics/Asteroids/Asteroid_9.png");
	gamewindow.loadAsteroidTexture("Graphics/Asteroids/Asteroid_10.png");

	gamewindow.loadAsteroidTexture("Graphics/Asteroids/scrap.png");
	gamewindow.loadAsteroidTexture("Graphics/Asteroids/scrap_2.png");
	gamewindow.loadAsteroidTexture("Graphics/Asteroids/scrap_3.png");
	gamewindow.loadAsteroidTexture("Graphics/Asteroids/scrap_4.png");
	gamewindow.loadAsteroidTexture("Graphics/Asteroids/scrap_5.png");
	gamewindow.loadAsteroidTexture("Graphics/Asteroids/scrap_6.png");
	gamewindow.loadAsteroidTexture("Graphics/Asteroids/scrap_7.png");
	gamewindow.loadAsteroidTexture("Graphics/Asteroids/scrap_8.png");
	gamewindow.loadAsteroidTexture("Graphics/Asteroids/scrap_9.png");
	gamewindow.loadAsteroidTexture("Graphics/Asteroids/scrap_10.png");
	gamewindow.loadAsteroidTexture("Graphics/Asteroids/scrap_11.png");
	gamewindow.loadAsteroidTexture("Graphics/Asteroids/scrap_12.png");
	gamewindow.loadAsteroidTexture("Graphics/Asteroids/scrap_13.png");
	gamewindow.loadAsteroidTexture("Graphics/Asteroids/scrap_14.png");
	gamewindow.loadAsteroidTexture("Graphics/Asteroids/scrap_15.png");

	gamewindow.loadFragmentTexture("Graphics/Projectiles/Fragment/frag.png");
	gamewindow.loadFragmentTexture("Graphics/Projectiles/Fragment/frag_2.png");
	gamewindow.loadFragmentTexture("Graphics/Projectiles/Fragment/frag_3.png");
	gamewindow.loadFragmentTexture("Graphics/Projectiles/Fragment/frag_4.png");
	gamewindow.loadFragmentTexture("Graphics/Projectiles/Fragment/frag_5.png");
	gamewindow.loadFragmentTexture("Graphics/Projectiles/Fragment/frag_6.png");
	gamewindow.loadFragmentTexture("Graphics/Projectiles/Fragment/frag_7.png");
	gamewindow.loadFragmentTexture("Graphics/Projectiles/Fragment/frag_8.png");
	gamewindow.loadFragmentTexture("Graphics/Projectiles/Fragment/frag_9.png");
	gamewindow.loadFragmentTexture("Graphics/Projectiles/Fragment/frag_10.png");

	gamewindow.loadPlanetTexture("Graphics/Planets/exo_2.jpg");

	gamewindow.loadStationTexture("Graphics/Stations/station.png");
	gamewindow.loadStationTexture("Graphics/Stations/station_2.png");
	gamewindow.loadStationTexture("Graphics/Stations/station_3.png");

	gamewindow.loadBackground("Graphics/Backgrounds/space_12.jpg", sf::Vector2f(0.5, 0.5));
	gamewindow.loadStart("Eris.jpg", sf::Vector2f(.25, .25));
	gamewindow.loadInv("Graphics/Buttons-Icons/Inv6x4.png", sf::Vector2f(472, 365));

	gamewindow.loadCrate("Graphics/Items/crate.jpg");

	gamewindow.GUImanager.loadFuel("Graphics/FuelMeter.png", sf::Vector2f(15, 300));
	gamewindow.GUImanager.loadHealth("Graphics/FuelMeter.png", sf::Vector2f(15, 300));

	gamewindow.GUImanager.loadGUI("Graphics/GuiBox.png", sf::Vector2f(0, 0));
	gamewindow.GUImanager.addBox(sf::Vector2f(0, 0), sf::Vector2f(30, 30));
	gamewindow.GUImanager.addBox(sf::Vector2f(32, 0), sf::Vector2f(120, 70));

	gamewindow.GUImanager.loadInfo("Graphics/Buttons-Icons/Info_2.png", sf::Vector2f(180, 600));
	gamewindow.GUImanager.loadHide("Graphics/Buttons-Icons/hide.png", sf::Vector2f(1, 1));
	gamewindow.GUImanager.loadShow("Graphics/Buttons-Icons/show.png", sf::Vector2f(1, 1));
	gamewindow.GUImanager.loadWASD("Graphics/Buttons-Icons/WASD.png");
	gamewindow.GUImanager.loadSPACE("Graphics/Buttons-Icons/Space.png");

	gamewindow.GUImanager.loadMenuBacking("Graphics/FuelMeter.png");
	gamewindow.GUImanager.loadButtonTexture("Graphics/Buttons-Icons/Button.png");
	gamewindow.GUImanager.loadSliderTexture("Graphics/Buttons-Icons/slideBar.png");
	gamewindow.GUImanager.loadSliderButtonTexture("Graphics/Buttons-Icons/slideButton.png");

	gamewindow.GUImanager.loadTextBox("Graphics/Buttons-Icons/TextBox.png");

	gamewindow.loadShipSpecs("ShipData.csv");
	gamewindow.loadProjectileSpecs("ProjectileData.csv");
	gamewindow.loadWaves("Waves.csv");
	gamewindow.loadItems("Items.csv");
	gamewindow.loadPlayer(sf::Vector2f(0, 0), sf::Vector2f(.3f, .3f), "Frigate");

	gamewindow.genChunks(sf::Vector2f(50000, 50000));

	gamewindow.run();

	system("pause");
}
