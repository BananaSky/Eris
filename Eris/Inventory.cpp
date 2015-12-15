#include "Inventory.hpp"
#include "Includes.hpp"
#include "Item.hpp"
#include "Window.hpp"
#include "ProjectileSpecs.hpp"

Inventory::Inventory()
{
	contents.reserve(width*height);
	for (int i = 0; i < width*height; i++)
	{
		contents.push_back(Item(true)); //Empty Items
	}
}

Inventory::~Inventory(){}

bool Inventory::insertNew(std::string type, Window* board, int amount)
{
	bool foundSpace = false;
	for (auto it = contents.begin(); it != contents.end(); ++it)
	{
		if (it->getName() == type)
		{
			it->addNum(amount);
			foundSpace = true;
			break;
		}
	}
	if (!foundSpace)
	{
		for (auto it = contents.begin(); it != contents.end(); ++it)
		{
			if (it->isEmpty)
			{
				*it = Item(false);
				it->setNum(amount);
				it->setName(board->getItems()->at(type).name);
				it->setTexture(*board->loadTexture(board->getItems()->at(type).texture));
				it->scale(sf::Vector2f(.9f, .9f));
				foundSpace = true;
				break;
			}
		}
	}

	return foundSpace;
}

bool Inventory::take(std::string type, int amount)
{
	for (auto it = contents.begin(); it != contents.end(); ++it)
	{
		if (it->getName() == type)
		{
			if (it->take(amount))
			{
				return true;
			}
			else
			{
				it->decrement();
				it->isEmpty = true;
				return false;
			}
		}
	}
	return false;
}

int Inventory::getNumOf(std::string type)
{
	int accumulator = 0;

	for (auto it = contents.begin(); it != contents.end(); ++it)
	{
		if (it->getName() == type)
		{
			accumulator += it->getAmountOf();
		}
	}

	return accumulator;
}


void Inventory::displayInv(sf::RenderWindow* window)
{
	for (Item& item : contents)
	{
		if (!item.isEmpty)
		{
			text.setPosition(item.getPosition());
			text.setString(item.getNumOf());
			window->draw(item);
			window->draw(text);
		}
	}
}

void Inventory::format(sf::RenderWindow* window)
{
	sf::Vector2i pos = sf::Vector2i((int)getPosition().x, (int)getPosition().y);

	pos.x += 57;
	int x_align = pos.x;
	pos.y += 45;

	int i = 0;
	for (int j = 0; j < height; j++)
	{
		for (int k = 0; k < width; k++)
		{
			if (i < contents.size())
			{
				contents[i].setPosition((float)pos.x, (float)pos.y);
			}
			else
			{
				break;
			}
			pos.x += cellSize;
			i++;
		}
		pos.x = x_align;
		pos.y += cellSize;
	}
}

sf::Vector2i Inventory::calcPosition(int index, sf::RenderWindow* window)
{
	sf::Vector2i pos = window->mapCoordsToPixel(sf::Vector2f(getPosition().x, getPosition().y));

	pos.x += 57;
	pos.y += 45;

	int i = 0;
	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < 8; k++)
		{
			if (i < contents.size())
			{
				if (i == index)
				{
					return pos;
				}
			}
			else
			{
				break;
			}
			pos.x += cellSize;
			i++;
		}

		pos.y += cellSize;
	}

	return pos;
}

int Inventory::calcIndex(sf::Vector2i position)
{
	return (position.x / cellSize) + (position.y / cellSize) * width;
}

void Inventory::InvListener(sf::Event* event, Window* board, sf::RenderWindow* window)
{
	sf::Vector2i pos = sf::Vector2i((int)getPosition().x, (int)getPosition().y);

	pos.x += 57;
	pos.y += 45;

	if (event->type == sf::Event::MouseButtonPressed && event->mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i mousePos = sf::Vector2i(event->mouseButton.x - pos.x, event->mouseButton.y - pos.y);
		
		if (mousePos.x / cellSize < width && mousePos.y / cellSize < height)
		{
			int index = calcIndex(mousePos);
			if (index < contents.size())
			{
				selected = index;
			}
		}
		
	}

	if (event->type == sf::Event::MouseMoved)
	{
		sf::Vector2i mousePos = sf::Vector2i(event->mouseMove.x, event->mouseMove.y);
		if (selected != -1)
		{
			contents[selected].setPosition(sf::Vector2f((float)(mousePos.x - cellSize / 2), (float)(mousePos.y - cellSize / 2)));
		}
	}

	if (event->type == sf::Event::MouseButtonReleased && event->mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i mousePos = sf::Vector2i(event->mouseButton.x - pos.x, event->mouseButton.y - pos.y);

		if (this->getLocalBounds().contains((sf::Vector2f)mousePos))
		{
			if (mousePos.x / cellSize < width && mousePos.y / cellSize < height && selected != -1)
			{
				int index = calcIndex(mousePos);
				if (index < contents.size())
				{
					std::iter_swap(contents.begin() + selected, contents.begin() + index);
					format(window);
					std::cout << "Moved Item to " << index << std::endl;
				}
			}
		}
		else
		{
			format(window);
		}
		
		selected = -1;
	}
}

std::vector<std::string> Inventory::getTypesOf(std::string type, Window* board)
{
	std::vector<std::string> typesOf;

	for (auto& i : contents)
	{
		auto got = board->getPSpecs()->find(i.getName());
		if (got != board->getPSpecs()->end() && got->second->Ammo_Type == type)
		{
			typesOf.push_back(i.getName());
		}
	}

	return typesOf;
}