#pragma once
#include "Includes.hpp"
#include "Slider.hpp"
#include "Button.hpp"

class Menu :
	public sf::RectangleShape
{
public:
	Menu();
	~Menu();

	void insertButton(Button button, sf::Vector2f pos);
	void insertSlider(Slider slider, sf::Vector2f pos);

	int  buttonListener(sf::Event * event);
	void sliderListener(sf::Event * event);

	void draw(sf::RenderWindow * window);

	float getRatioOf(int index) { if (index < sliders.size()) { return sliders[index].getRatio(); } }

	void loadButtonTexture       (sf::Texture* t) { for (Button& b : buttons) { b.setTexture(t); } }
	void loadSliderTexture       (sf::Texture* t) { for (Slider& s : sliders) { s.setTexture(t); } }
	void loadSliderButtonTexture (sf::Texture* t) { for (Slider& s : sliders) { s.setButtonTexture(t); } }

private:
	std::vector<Slider> sliders;
	std::vector<Button> buttons;
};

