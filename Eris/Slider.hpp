#pragma once
#include "Includes.hpp"
class Slider :
	public sf::RectangleShape
{
public:
	Slider();
	~Slider();

	void move(sf::Vector2f);
	void listener(sf::Event * event);
	void draw(sf::RenderWindow *);

	float getRatio();

	void setButtonTexture(sf::Texture* t) { slidingButton.setTexture(t); }

private:

	sf::RectangleShape slidingButton;
	static int margin;
	bool beingMoved = false;
};

