#pragma once
#include "Includes.hpp"
#include "Menu.hpp"
#include "TimedTextBox.hpp"

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

	void guiListener         (sf::Event * event, Window * board, sf::RenderWindow * window);
	void stationMenuListener (sf::Vector2i pos);
	void planetMenuListener  (sf::Vector2i pos);

	void planetGUI (sf::RenderWindow * window);
	void stationGUI(sf::RenderWindow * window);
	void InfoGUI();

	void addBox            (sf::Vector2f position, sf::Vector2f size);
	void addMessage        (std::string m) { output.insert(m); }
	void DrawCascadingText (std::string output, int offset);


	void setTarget     (sf::RenderWindow* window) { target = window; }
	void setParent     (Window* board)            { parent = board; }
	void setNearStation(bool set)                 { nearStation = set; }
	void setNearPlanet (bool set)                 { nearPlanet = set; }

	void openStationMenu() { stationMenuOpen = !stationMenuOpen; }
	void openPlanetMenu()  { planetMenuOpen = !planetMenuOpen; }

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

	Menu stationMenu;
	Menu planetMenu;

	TimedTextBox output;

	sf::RectangleShape info;
	sf::Sprite         hideButton; //Should make a button class
	sf::Sprite         showButton;


	bool infoHidden      = false;
	bool nearStation     = false;
	bool nearPlanet      = false;
	bool stationMenuOpen = false;
	bool planetMenuOpen  = false;

	bool showAimingLine  = true;
};

