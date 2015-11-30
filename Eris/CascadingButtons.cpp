#include "CascadingButtons.hpp"

CascadingButtons::CascadingButtons(){}

CascadingButtons::~CascadingButtons(){}

void CascadingButtons::setSections(int num_sections)
{
	if (sections != num_sections)
	{
		sections = num_sections;

		clickAreas.clear();

		float d_y = this->getSize().y / (float)num_sections;
		sf::Vector2f size(getSize().x, d_y);

		for (int i = 0; i < num_sections; i++)
		{
			clickAreas.push_back(sf::FloatRect(sf::Vector2f(getPosition().x, getPosition().y + d_y * i),
												size));
		}
	}
}

int CascadingButtons::clickListener(sf::Vector2i pos)
{
	for (int i = 0; i < clickAreas.size(); i++)
	{
		if (clickAreas[i].contains((sf::Vector2f)pos))
		{
			return (i + 1);
		}
	}
}