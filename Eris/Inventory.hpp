#pragma once

#include "Includes.hpp"
#include "Item.hpp"

class Window;


class Inventory :
	public sf::RectangleShape
{
public:
	Inventory();
	~Inventory();

	bool insertNew(std::string location, Window * board, int amount=1);
	bool take(std::string type, int amount=1);

	int getNumOf(std::string type);

	void displayInv(sf::RenderWindow*);

	void format(sf::RenderWindow*);

	sf::Vector2i calcPosition(int index, sf::RenderWindow * window);

	int calcIndex(sf::Vector2i position);

	void loadText(sf::Text t) { text = t; text.setCharacterSize(16); text.setColor(sf::Color(255, 255, 255, 180)); }

	void InvListener(sf::Event *, Window * board, sf::RenderWindow * window);

	std::vector<std::string> getTypesOf(std::string type, Window * board);

	int cellSize = 58; //Three pixel Wide Dividers
	int width = 6;
	int height = 4;

	std::vector<Item> contents;
	int selected = -1;

	sf::Text text;
};

