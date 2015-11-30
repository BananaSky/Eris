#pragma once
#include "Includes.hpp"
class Button :
	public sf::RectangleShape
{
public:
	Button();
	~Button();

	Button(sf::Vector2f size, std::string string, sf::Text text);

	bool listener(sf::Vector2f pos);
	void setText(std::string newText);
	void loadText(sf::Text text);

	void format();

	void draw(sf::RenderWindow * window);

private:

	static int margin; 
	sf::Text text;
};

