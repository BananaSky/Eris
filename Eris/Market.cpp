#include "Market.hpp"
#include "Window.hpp"

Market::Market(){}

Market::~Market(){}

void Market::addRandomMarketItem(Window* board)
{
	modifier = (float)(rand() % 100 + 50) / 100.0f;

	std::vector<std::string> keys;
	keys.reserve(board->getItems()->size());

	for (auto &kv : *board->getItems())
	{
		keys.push_back(kv.first);
	}

	int maxItems = 2;

	std::vector<int> taken;
	taken.reserve(maxItems);

	int numItems = rand() % maxItems + 1;

	for (int i = 0; i < numItems; i++)
	{
		int selector = rand() % keys.size();
		taken.push_back(selector);
		std::string type = keys[selector];
		int chance = rand() % 100 + 1;
		bool selling;
		if (chance < 50) { selling = false; }
		else { selling = true; }

		insert(std::pair<bool, ItemSpecs>(selling, board->getItems()->at(type)));
	}
}

void Market::determineAction(int n, Window* board, float percent)
{
	if (n >= 0 && n < market.size())
	{
		if (market[n].first) //If selling
		{
			board->buy(market[n].second.name, percent);
		}
		else //If buying
		{
			board->sell(market[n].second.name, percent);
		}
	}
}