#include "GuiManager.hpp"
#include "Includes.hpp"
#include "Window.hpp"

GuiManager::GuiManager()
{
	if (!font.loadFromFile("Graphics/Fonts/SUSANNA_.ttf"))
	{

	}
	text.setFont(font);
	text.setColor(sf::Color::White);

	output.setSize(sf::Vector2f(100, 200));
	output.loadTextSize(12);
	output.setSpace(14);
	output.loadFont(font);
	output.setPosition(32, 72);
}
GuiManager::~GuiManager(){}

GuiManager::GuiManager(Window* board, sf::RenderWindow* window)
{
	parent = board;
	target = window;
	if (!font.loadFromFile("Graphics/Fonts/SUSANNA_.ttf"))
	{

	}
	text.setFont(font);
	text.setColor(sf::Color::White);

	output.setPosition(sf::Vector2f(window->getSize().x - output.getSize().x, 0));
	output.loadTextSize(16);
	output.setSpace(20);
	output.loadFont(font);
}

void GuiManager::addBox(sf::Vector2f position, sf::Vector2f size)
{
	guiBoxes.push_back(sf::RectangleShape(size));
	guiBoxes.back().setPosition(position);
	guiBoxes.back().setTexture(&guiBox);
}

void GuiManager::guiListener(sf::Event* event, Window* board, sf::RenderWindow* window)
{
	
	if (event->type == sf::Event::MouseButtonPressed && event->mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i pos = sf::Vector2i(event->mouseButton.x, event->mouseButton.y);

		stationMenuListener(pos);
		planetMenuListener(pos);

		if (hideButton.getGlobalBounds().contains((sf::Vector2f)pos))
		{
			infoHidden = true;
		}
		else if (showButton.getGlobalBounds().contains((sf::Vector2f)pos))
		{
			infoHidden = false;
		}
	}
	if (event->type == sf::Event::MouseButtonReleased && event->mouseButton.button == sf::Mouse::Left)
	{
		
	}
}

void GuiManager::stationMenuListener(sf::Vector2i pos)
{
	if (stationMenuOpen)
	{
		switch (stationMenu.clickListener(pos))
		{
		case 1:
			parent->getPlayer()->upgrade(parent);
			break;
		case 2:
			parent->getPlayer()->refuel(parent);
			break;
		case 3:
			parent->getPlayer()->refill(parent);
			break;
		case 4:
			parent->getPlayer()->repair(parent);
			break;
		default:
			break;
		};
	}
}

void GuiManager::planetMenuListener(sf::Vector2i pos)
{
	if (planetMenuOpen)
	{
		switch (planetMenu.clickListener(pos))
		{
		case 1:
			parent->buyIron();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			break;
		}
	}
}

void GuiManager::planetGUI(sf::RenderWindow* window)
{
	if (!planetMenuOpen)
	{
		text.setCharacterSize(30);
		text.setPosition(142, 2);
		text.setColor(sf::Color(255, 163, 102));
		text.setString("X to open planet menu");
		window->draw(text);
	}
	else
	{
		window->draw(planetMenu);
	}
}

void GuiManager::DrawCascadingText(std::string output, int offset)
{
	text.setPosition(text.getPosition().x, text.getPosition().y + offset);
	text.setString(output);
	target->draw(text);
}

void GuiManager::InfoGUI()
{
	text.setFont(font);
	text.setCharacterSize(25);
	text.setColor(sf::Color(255, 212, 128));

	hideButton.setPosition(target->getSize().x - hideButton.getGlobalBounds().width, info.getSize().y);
	showButton.setPosition(target->getSize().x - showButton.getGlobalBounds().width, 0);
	info.setPosition(target->getSize().x - info.getGlobalBounds().width, 0);
	target->draw(hideButton);
	target->draw(info);

	text.setPosition(info.getPosition().x + 25, info.getPosition().y + 13);
	text.setString(parent->getPlayer()->getType());
	target->draw(text);

	text.setCharacterSize(20);
	DrawCascadingText("Equipped: " + parent->getPlayer()->getEquipped(), 50);
	int spacing = 30;
	DrawCascadingText("Range: " + std::to_string(parent->getPlayer()->getRange(parent)), spacing);
	DrawCascadingText("Max DPS: " + std::to_string(parent->getPlayer()->getDPS(parent)), spacing);
	DrawCascadingText("Aiming: " + parent->getPlayer()->getAiming(), spacing);
	DrawCascadingText("Velocity: " + std::to_string(parent->getPlayer()->getVelocity()), spacing);
	DrawCascadingText("Mass: " + std::to_string(parent->getPlayer()->getMass()), spacing);
	DrawCascadingText("Max Acceleration: " + std::to_string(parent->getPlayer()->getAccel()), spacing);
	DrawCascadingText("Efficiency: " + std::to_string(parent->getPlayer()->getEfficiency()), spacing);
	DrawCascadingText("Fuel: " + parent->getPlayer()->getFuelString(), spacing);
	DrawCascadingText("Ammo: " + parent->getPlayer()->getAmmoString(), spacing);
	DrawCascadingText("Structure: " + parent->getPlayer()->getStructString(), spacing);

	text.setColor(sf::Color::White);
}

void GuiManager::stationGUI(sf::RenderWindow* window)
{
	if (!stationMenuOpen)
	{
		text.setCharacterSize(30);
		text.setString("X to open station menu");
		text.setColor(sf::Color(255, 163, 102));
		text.setPosition(142, 2);
		window->draw(text);
	}
	else
	{
		window->draw(stationMenu);
	}
}

void GuiManager::draw(sf::RenderWindow* window)
{
	window->draw(output);
	output.draw(window);
	output.update();

	for (sf::RectangleShape& box : guiBoxes)
	{
		window->draw(box);
	}

	text.setPosition(2, 2);
	text.setString(std::to_string((int)parent->getFps()));
	text.setCharacterSize(24);
	window->draw(text);

	text.setCharacterSize(16);
	text.setString("Score: " + std::to_string(parent->getScore()));
	text.setPosition(36, 2);
	window->draw(text);

	text.setString("Credits: " + std::to_string(parent->getBalance()));
	text.setPosition(36, 32);
	window->draw(text);

	if (nearStation) { stationGUI(window); }
	else             { stationMenuOpen = false; }

	if (nearPlanet)  { planetGUI(target);  }
	else             { planetMenuOpen = false; }

	if (!infoHidden) { InfoGUI(); }
	else             { window->draw(showButton); }

	window->draw(*parent->getPlayer()->getFuel());
	window->draw(*parent->getPlayer()->getHealth());
	window->draw(*parent->getPlayer()->getAmmo());
	window->draw(ammo);
	window->draw(fuel);
	window->draw(health);
}

void GuiManager::update()
{
	
}

