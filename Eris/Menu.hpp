#pragma once
#include "Includes.hpp"
class Menu :
	public sf::RectangleShape
{
public:
	Menu();
	~Menu();

	void setSections(int x);
	int clickListener(sf::Vector2i pos);
	std::vector<sf::FloatRect> clickAreas;

private:
	int sections;
};
