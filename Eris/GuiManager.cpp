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
	text.setCharacterSize(16);

	output.setSize(sf::Vector2f(200, 200));
	output.loadTextSize(12);
	output.setSpace(14);
	output.loadFont(font);
	output.setPosition(32, 72);

	recticle.setOutlineColor(sf::Color(204, 255, 255, 200));
	recticle.setFillColor(sf::Color::Transparent);
	recticle.setOutlineThickness(10);
	recticle.setRadius(50);
	recticle.setOrigin(50, 50);

	aimingLine.setFillColor(sf::Color(204, 255, 255, 255));
	aimingLine.setSize(sf::Vector2f(10000000, 4));
	aimingLine.setOrigin(5000000, 2);

	stationMenu.setPosition(154, 0);
	stationMenu.setSize(sf::Vector2f(200, 200));
	stationMenu.insertButton(Button(sf::Vector2f(60, 30), "Upgrade", text), sf::Vector2f(10, 10));
	stationMenu.insertButton(Button(sf::Vector2f(60, 30), "Refuel", text),  sf::Vector2f(10, 50));
	stationMenu.insertButton(Button(sf::Vector2f(60, 30), "Refill", text),  sf::Vector2f(10, 90));
	stationMenu.insertButton(Button(sf::Vector2f(60, 30), "Repair", text),  sf::Vector2f(10, 130));
	stationMenu.insertSlider(Slider(), sf::Vector2f(70, 50));
	stationMenu.insertSlider(Slider(), sf::Vector2f(70, 90));
	stationMenu.insertSlider(Slider(), sf::Vector2f(70, 130));

	planetMenu.setPosition(154, 0);
	planetMenu.setSize(sf::Vector2f(200, 200));
	planetMenu.insertButton(Button(sf::Vector2f(60, 30), "Buy Iron", text), sf::Vector2f(10, 10));
	//planetMenu.insertButton(Button(sf::Vector2f(60, 30), "Refuel", text), sf::Vector2f(10, 50));
	//planetMenu.insertButton(Button(sf::Vector2f(60, 30), "Refill", text), sf::Vector2f(10, 90));
	//planetMenu.insertButton(Button(sf::Vector2f(60, 30), "Repair", text), sf::Vector2f(10, 130));
	//planetMenu.insertSlider(Slider(), sf::Vector2f(70, 50));
	//planetMenu.insertSlider(Slider(), sf::Vector2f(70, 90));
	//planetMenu.insertSlider(Slider(), sf::Vector2f(70, 130));
} 

GuiManager::~GuiManager(){}

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

		if (hideButton.getGlobalBounds().contains((sf::Vector2f)pos))
		{
			infoHidden = true;
		}
		else if (showButton.getGlobalBounds().contains((sf::Vector2f)pos))
		{
			infoHidden = false;
		}
	}

	stationMenuListener(event);
}

void GuiManager::stationMenuListener(sf::Event* event)
{
	if (stationMenuOpen)
	{
		stationMenu.sliderListener(event);
		switch (stationMenu.buttonListener(event))
		{
		case 1:
			parent->getPlayer()->upgrade(parent);
			break;
		case 2:
			std::cout << stationMenu.getRatioOf(0) << std::endl;
			parent->getPlayer()->refuel(parent, stationMenu.getRatioOf(0));
			break;
		case 3:
			std::cout << stationMenu.getRatioOf(1)  << std::endl;
			parent->getPlayer()->refill(parent, stationMenu.getRatioOf(1));
			break;
		case 4:
			std::cout << stationMenu.getRatioOf(2) << std::endl;
			parent->getPlayer()->repair(parent, stationMenu.getRatioOf(2));
			break;
		default:
			break;
		};
	}
}

void GuiManager::planetMenuListener(sf::Event* event)
{
	if (planetMenuOpen)
	{
		planetMenu.sliderListener(event);
		switch (planetMenu.buttonListener(event))
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
	if (planetMenuOpen)
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

void GuiManager::setNearStation(bool set)
{
	nearStation = set;
}

void GuiManager::setNearPlanet(bool set)
{
	nearPlanet = set;
}

void GuiManager::openStationMenu()
{
	stationMenuOpen = !stationMenuOpen; parent->pause();
}

void GuiManager::openPlanetMenu()
{
	planetMenuOpen = !planetMenuOpen;  parent->pause();
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
	DrawCascadingText("Equipped: " + parent->getPlayer()->getEquipped(), 75);
	int spacing = 30;
	DrawCascadingText("Range: "            + std::to_string(parent->getPlayer()->getRange(parent)), spacing);
	DrawCascadingText("Max DPS: "          + std::to_string(parent->getPlayer()->getDPS(parent)), spacing);
	DrawCascadingText("Accuracy: "         + parent->getPlayer()->getAccString(), spacing);
	DrawCascadingText("Aiming: "           + parent->getPlayer()->getAiming(), spacing);
	DrawCascadingText("Velocity: "         + std::to_string(parent->getPlayer()->getVelocity()), spacing);
	DrawCascadingText("Strafe Velocity: "  + std::to_string((int)parent->getPlayer()->getStrafe()), spacing);
	DrawCascadingText("Max Acceleration: " + std::to_string(parent->getPlayer()->getAccel()), spacing);
	DrawCascadingText("Efficiency: "       + std::to_string(parent->getPlayer()->getEfficiency()), spacing);
	DrawCascadingText("Fuel: "             + parent->getPlayer()->getFuelString(), spacing);
	DrawCascadingText("Ammo: "             + parent->getPlayer()->getAmmoString(), spacing);
	DrawCascadingText("Structure: "        + parent->getPlayer()->getStructString(), spacing);

	text.setColor(sf::Color::White);
}

void GuiManager::stationGUI(sf::RenderWindow* window)
{
	if (stationMenuOpen)
	{
		stationMenu.draw(window);
	}
}

void GuiManager::drawBacking(sf::RenderWindow* window)
{
	if (showAimingLine)
	{
		window->setView(parent->getNormalView());
		window->draw(aimingLine);
		window->draw(recticle);
		window->setView(parent->getGUIview());
	}
}

void GuiManager::draw(sf::RenderWindow* window)
{
	//window->draw(output);
	output.draw(window);
	output.update();

	for (sf::RectangleShape& box : guiBoxes)
	{
		window->draw(box);
	}

	text.setPosition(2, 2);
	text.setString(std::to_string((int)parent->getFps()));
	text.setCharacterSize(18);
	window->draw(text);

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
	aimingLine.setRotation(parent->getPlayer()->getRotation());
	aimingLine.setPosition(parent->getPlayer()->getPosition());

	float range = (float)parent->getPlayer()->getRange(parent);

	float d_x = (float)(range * cos(parent->getPlayer()->getRotation() * 0.0174533));
	float d_y = (float)(range * sin(parent->getPlayer()->getRotation() * 0.0174533));

	if (parent->getPlayer()->isAimingFront())
	{
		recticle.setPosition(aimingLine.getPosition().x + d_x, aimingLine.getPosition().y + d_y);
	}
	else
	{
		recticle.setPosition(aimingLine.getPosition().x - d_x, aimingLine.getPosition().y - d_y);
	}
}

