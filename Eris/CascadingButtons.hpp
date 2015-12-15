#pragma once
#include "Includes.hpp"
class CascadingButtons :
	public sf::RectangleShape
{
public:
	CascadingButtons();
	~CascadingButtons();

	void setSections(int x);
	int clickListener(sf::Vector2i pos);
	std::vector<sf::FloatRect> clickAreas;

private:
	int sections;
};
