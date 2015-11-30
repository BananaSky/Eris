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

	bool insertNew(std::string location, Window * board);

	void displayInv(sf::RenderWindow*);

	void format(sf::RenderWindow*);

	sf::Vector2i calcPosition(int index, sf::RenderWindow * window);

	int calcIndex(sf::Vector2i position);

	void InvListener(sf::Event *, Window * board, sf::RenderWindow * window);

	int cellSize = 58; //Three pixel Wide Dividers
	int width = 6;
	int height = 4;

	std::vector<Item> contents;
	int selected = -1;
};

