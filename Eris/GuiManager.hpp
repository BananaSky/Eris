#pragma once
#include "Includes.hpp"
#include "CascadingButtons.hpp"
#include "TimedTextBox.hpp"
#include "Menu.hpp"

class Window;

class GuiManager
{
public:
	GuiManager();
	~GuiManager();

	void update();
	void draw(sf::RenderWindow * window);

	void loadGUI         (std::string location, sf::Vector2f scale);
	void loadHide        (std::string location, sf::Vector2f scale);
	void loadShow        (std::string location, sf::Vector2f scale);
	void loadFuel		 (std::string location, sf::Vector2f size);
	void loadHealth		 (std::string location, sf::Vector2f size);
	void loadAmmo		 (std::string location, sf::Vector2f size);
	void loadInfo		 (std::string location, sf::Vector2f size);
	void loadStationMenu (std::string location, sf::Vector2f size);
	void loadPlanetMenu  (std::string location, sf::Vector2f size);
	void loadTextBox     (std::string location);
	void loadMenuBacking (std::string location);

	void loadButtonTexture(std::string location);

	void loadSliderButtonTexture(std::string location);

	void loadSliderTexture(std::string location);

	void guiListener         (sf::Event * event, Window * board, sf::RenderWindow * window);
	void stationMenuListener(sf::Event * event);
	void planetMenuListener (sf::Event * event);

	void planetGUI (sf::RenderWindow * window);
	void stationGUI(sf::RenderWindow * window);
	void InfoGUI();

	void addBox            (sf::Vector2f position, sf::Vector2f size);
	void addMessage        (std::string m) { output.insert(m); }
	void DrawCascadingText (std::string output, int offset);


	void setTarget     (sf::RenderWindow* window) { target = window; }
	void setParent     (Window* board)            { parent = board; }
	void setNearStation(bool set);
	void setNearPlanet(bool set);

	void openStationMenu();
	void openPlanetMenu(); 

	bool isNearStation() { return nearStation; }
	bool isNearPlanet()  { return nearPlanet; }

	sf::RectangleShape* getFuel() { return &fuel; }

private:
	Window*           parent;
	sf::RenderWindow* target;

	sf::Font font;
	sf::Text text;

	sf::RectangleShape fuel;
	sf::RectangleShape health;
	sf::RectangleShape ammo;

	sf::RectangleShape aimingLine;
	sf::CircleShape    recticle;

	sf::Texture                     guiBox;  //Non interactive boxes
	std::vector<sf::RectangleShape> guiBoxes;

	//Textures for menus
	sf::Texture                     menuBacking;
	sf::Texture                     buttonTexture;
	sf::Texture                     sliderButtonTexture;
	sf::Texture                     sliderTexture;

	Menu planetMenu;
	Menu stationMenu;

	TimedTextBox output;

	sf::RectangleShape info;
	sf::Sprite         hideButton; //Should be updated to be buttons instead of sprites
	sf::Sprite         showButton;


	bool infoHidden      = false;
	bool nearStation     = false;
	bool nearPlanet      = false;
	bool stationMenuOpen = false;
	bool planetMenuOpen  = false;

	bool showAimingLine  = false;
};
