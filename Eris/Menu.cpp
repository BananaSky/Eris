#include "Menu.hpp"
#include "GuiManager.hpp"

Menu::Menu(){}

Menu::~Menu(){}

sf::Texture Menu::buttonTexture;
sf::Texture Menu::sliderTexture;
sf::Texture Menu::sliderButtonTexture;

void Menu::insertButton(Button button, sf::Vector2f pos) 
{
	buttons.push_back(button);
	buttons.back().setPosition(getPosition().x + pos.x, getPosition().y + pos.y);
	buttons.back().format();
	buttons.back().setTexture(&buttonTexture);
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
			std::cout << "Checking against: " << i << std::endl;
			if (buttons[i].listener((sf::Vector2f)pos))
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
	window->draw(*this);

	for (Slider& s : sliders)
	{
		s.draw(window);
	}
	for (Button& b : buttons)
	{
		b.draw(window);
	}
}