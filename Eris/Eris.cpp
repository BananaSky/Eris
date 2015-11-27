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

	gamewindow.loadPlanetTexture("Graphics/Planets/exo_2.jpg");

	gamewindow.loadStationTexture("Graphics/Stations/station.png");
	gamewindow.loadStationTexture("Graphics/Stations/station_2.png");
	gamewindow.loadStationTexture("Graphics/Stations/station_3.png");

	gamewindow.loadBackground("Graphics/Backgrounds/space_12.jpg", sf::Vector2f(0.5, 0.5));
	gamewindow.loadFuel("Graphics/FuelMeter.png", sf::Vector2f(15, 300));
	gamewindow.loadHealth("Graphics/FuelMeter.png", sf::Vector2f(15, 300));
	gamewindow.loadAmmo("Graphics/FuelMeter.png", sf::Vector2f(15, 300));
	gamewindow.loadGUI("Graphics/GuiBox.png", sf::Vector2f(0, 0));
	gamewindow.loadStart("Eris.jpg", sf::Vector2f(.25, .25));
	gamewindow.addBox(sf::Vector2f(0, 0), sf::Vector2f(30, 30));

	gamewindow.loadShipSpecs("ShipData.csv");
	gamewindow.loadProjectileSpecs("ProjectileData.csv");
	gamewindow.loadPlayer(sf::Vector2f(0, 0), sf::Vector2f(.3f, .3f), "Frigate");

	gamewindow.genChunks(sf::Vector2f(50000, 50000));

	gamewindow.run();

	system("pause");
}