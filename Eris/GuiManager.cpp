#include "GuiManager.hpp"
#include "Includes.hpp"
#include "Window.hpp"

GuiManager::GuiManager(){}
GuiManager::~GuiManager(){}

GuiManager::GuiManager(Window* window)
{
	parent = window;
}

void GuiManager::guiListener(sf::Event* event, Window* board, sf::RenderWindow* window)
{

}

void GuiManager::draw(sf::RenderWindow* window)
{

}

void GuiManager::update()
{
	
}


void GuiManager::loadStationMenu(std::string location, sf::Vector2f size)
{
	stationMenu.setTexture(parent->loadTexture(location));
	stationMenu.setSize(size);
	stationMenu.setPosition(132, 2);
}

void GuiManager::loadPlanetMenu(std::string location, sf::Vector2f size)
{
	planetMenu.setTexture(parent->loadTexture(location));
	planetMenu.setSize(size);
	planetMenu.setPosition(132, 2);
}