#pragma once
#include "Includes.hpp"

class Window;

class GuiManager
{
public:
	GuiManager();
	~GuiManager();
	GuiManager(Window * window);
	void guiListener(sf::Event * event, Window * board, sf::RenderWindow * window);
	void draw(sf::RenderWindow * window);
	void update();
	void loadStationMenu(std::string location, sf::Vector2f size);
	void loadPlanetMenu(std::string location, sf::Vector2f size);
	void setParent(Window* board) { parent = board; }

private:
	Window* parent;

	sf::RectangleShape stationMenu;
	sf::RectangleShape planetMenu;

};

