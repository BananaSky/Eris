#pragma once
#include "Includes.hpp"

class TimedText :
	public sf::Text
{
public:
	TimedText();
	~TimedText();

	void update();
	int  getCurrentDuration() { return duration; }
	void setDuration(int n)   { duration = n; }

private:
	int duration = 255;
};

