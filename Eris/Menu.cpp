#include "Menu.hpp"
#include "GuiManager.hpp"

Menu::Menu()
{
	closeButton.setSize(sf::Vector2f(10, 10));
	closeButton.setFillColor(sf::Color::Red);
}

Menu::~Menu(){}

sf::Texture Menu::buttonTexture;
sf::Texture Menu::sliderTexture;
sf::Texture Menu::sliderButtonTexture;

bool Menu::closeListener(sf::Event* event)
{
	if (event->type == sf::Event::MouseButtonPressed && event->mouseButton.button == sf::Mouse::Left)
	{
		if (closeButton.listener(sf::Vector2f(event->mouseButton.x, event->mouseButton.y)))
		{
			return true;
		}
	}
	return false;
}

void Menu::insertButton(Button button, sf::Vector2f pos) 
{
	buttons.push_back(button);
	buttons.back().setPosition(getPosition().x + pos.x, getPosition().y + pos.y);
	buttons.back().format();
	buttons.back().setTexture(&buttonTexture);
}

void Menu::insertSecondaryButton(Button button, sf::Vector2f pos)
{
	secondaryButtons.push_back(button);
	secondaryButtons.back().setPosition(getPosition().x + pos.x, getPosition().y + pos.y);
	secondaryButtons.back().format();
	secondaryButtons.back().setTexture(&buttonTexture);
}

void Menu::insertSlider(Slider slider, sf::Vector2f pos)
{
	sliders.push_back(slider);
	sliders.back().move(sf::Vector2f(getPosition().x + pos.x, getPosition().y + pos.y)); // Sets Position of slider button as well;
	sliders.back().setTexture(&sliderTexture);
	sliders.back().setButtonTexture(&sliderButtonTexture);
}

void Menu::insertRow(std::string label)
{
	insertButton(Button(sf::Vector2f(60, 30), label, *parent->getText()), sf::Vector2f(x, y));
	insertSlider(Slider(), sf::Vector2f(x + horizontalSpacing, y));
	buttons.back().setTexture(&buttonTexture);
	sliders.back().setTexture(&sliderTexture);
	sliders.back().setButtonTexture(&sliderButtonTexture);
	y += verticalSpacing;
}

int Menu::buttonListener(sf::Event* event)
{
	if (event->type == sf::Event::MouseButtonPressed && event->mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i pos(event->mouseButton.x, event->mouseButton.y);

		for (int i = 0; i < buttons.size(); i++)
		{
			if (buttons[i].listener((sf::Vector2f)pos))
			{
				return  i;
			}
		}
	}

	return -1;
}

int Menu::secondaryButtonListener(sf::Event* event)
{
	if (event->type == sf::Event::MouseButtonPressed && event->mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i pos(event->mouseButton.x, event->mouseButton.y);

		for (int i = 0; i < secondaryButtons.size(); i++)
		{
			if (secondaryButtons[i].listener((sf::Vector2f)pos))
			{
				return  i;
			}
		}
	}

	return -1;
}

void Menu::sliderListener(sf::Event* event)
{
	for (Slider& s : sliders)
	{
		s.listener(event);
	}
}

void Menu::draw(sf::RenderWindow* window)
{
	//window->draw(*this);
	closeButton.setPosition(this->getPosition().x - closeButton.getSize().x + this->getSize().x, this->getPosition().y);
	closeButton.draw(window);

	for (Slider& s : sliders)
	{
		s.draw(window);
	}

	for (Button& b : buttons)
	{
		b.draw(window);
	}
	
	for (Button& b : secondaryButtons)
	{
		b.draw(window);
	}
}