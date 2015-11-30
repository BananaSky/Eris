#include "Menu.hpp"

Menu::Menu(){}

Menu::~Menu(){}

void Menu::insertButton(Button button, sf::Vector2f pos) 
{
	buttons.push_back(button);
	buttons.back().setPosition(getPosition().x + pos.x, getPosition().y + pos.y);
	buttons.back().format();
}

void Menu::insertSlider(Slider slider, sf::Vector2f pos)
{
	sliders.push_back(slider);
	sliders.back().move(sf::Vector2f(getPosition().x + pos.x, getPosition().y + pos.y)); // Sets Position of slider button as well;
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
				return  i + 1;
			}
		}
	}

	return 0;
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