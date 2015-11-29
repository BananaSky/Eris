#include "TimedText.hpp"

TimedText::TimedText(){}

TimedText::~TimedText(){}

void TimedText::update()
{
	if (duration > 0)
	{
		duration--;

		sf::Color next = getColor();
		if (next.a > 0)
		{
			next.a--;
			setColor(next);
		}
	}
}