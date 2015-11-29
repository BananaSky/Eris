#pragma once
#include "Includes.hpp"
#include "TimedText.hpp"

class TimedTextBox :
	public sf::RectangleShape
{
public:
	TimedTextBox();
	~TimedTextBox();

	void insert(std::string message);

	void format();
	void update();

	void draw(sf::RenderWindow * window);

	void loadTextColor(sf::Color n) { textColor = n; }
	void loadFont(sf::Font n)       { font = n;      }
	void loadTextSize(int n)        { textSize = n;  }

	void setDuration(int n) { duration = n; }
	void setSpace(int n)    { spacing = n; }

private:

	int margin   = 10;  //In pixels
	int spacing  = 20;
	int textSize = 16;
	int duration = 255; //In frames
	sf::Font font;
	sf::Color textColor = sf::Color::White;
	std::vector<TimedText> output;
};

