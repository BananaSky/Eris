#pragma once

#include "ItemSpecs.hpp"
#include "Item.hpp"

class Window;

class Market
{
public:
	Market();
	~Market();

	void addRandomMarketItem(Window* board);

	void determineAction(int n, Window * board, float percent);

	void insert(std::pair<bool, ItemSpecs> pair) { market.push_back(pair); }

	std::vector< std::pair<bool, ItemSpecs> >* getMarket() { return &market; }

private:

	std::vector< std::pair<bool, ItemSpecs> > market;
	float modifier = 1.0;
};

