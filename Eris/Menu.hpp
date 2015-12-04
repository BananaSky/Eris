#pragma once
#include "Includes.hpp"
#include "Slider.hpp"
#include "Button.hpp"

class GuiManager;

class Menu :
	public sf::RectangleShape
{
public:
	Menu();
	~Menu();

	void insertButton(Button button, sf::Vector2f pos);
	void insertSlider(Slider slider, sf::Vector2f pos);

	void insertRow(std::string label);

	int  buttonListener(sf::Event * event);
	void sliderListener(sf::Event * event);

	void draw(sf::RenderWindow * window);

	float getRatioOf(int index) { if (index < sliders.size()) { return sliders[index].getRatio(); } }

	void loadButtonTexture       (sf::Texture* t) { for (Button& b : buttons) { b.setTexture(t); } }
	void loadSliderTexture       (sf::Texture* t) { for (Slider& s : sliders) { s.setTexture(t); } }
	void loadSliderButtonTexture (sf::Texture* t) { for (Slider& s : sliders) { s.setButtonTexture(t); } }

	void setParent(GuiManager* set) { parent = set; }
	void clear() { sliders.clear(); buttons.clear(); }

private:
	std::vector<Slider> sliders;
	std::vector<Button> buttons;

	GuiManager* parent;

	int x = 20; //Initial offsets from the menu's position
	int y = 20;
	int verticalSpacing = 40;
	int horizontalSpacing = 40;
};

