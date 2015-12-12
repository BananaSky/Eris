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
	void insertSecondaryButton(Button button, sf::Vector2f pos);
	void insertSlider(Slider slider, sf::Vector2f pos);

	void insertRow(std::string label);

	int  buttonListener(sf::Event * event);
	int  secondaryButtonListener(sf::Event * event);
	void sliderListener(sf::Event * event);
	bool closeListener(sf::Event* event);

	void draw(sf::RenderWindow * window);

	float getRatioOf(int index) { if (index < sliders.size()) { return sliders[index].getRatio(); } else { return .1f; } }

	void loadButtonTexture      (sf::Texture* t) { buttonTexture = *t;       for (Button& b : buttons) { b.setTexture(t); } }
	void loadSliderTexture      (sf::Texture* t) { sliderTexture = *t;       for (Slider& s : sliders) { s.setTexture(t); } }
	void loadSliderButtonTexture(sf::Texture* t) { sliderButtonTexture = *t; for (Slider& s : sliders) { s.setButtonTexture(t); } }

	void setParent(GuiManager* set) { parent = set; }
	void clear() { sliders.clear(); buttons.clear(); secondaryButtons.clear(); x = 20; y = 20; }

private:
	std::vector<Slider> sliders;
	std::vector<Button> buttons;
	std::vector<Button> secondaryButtons;
	Button closeButton;

	GuiManager* parent;

	static sf::Texture buttonTexture;
	static sf::Texture sliderTexture;
	static sf::Texture sliderButtonTexture;

	float x = 20; //Initial offsets from the menu's position
	float y = 20;
	float verticalSpacing = 40;
	float horizontalSpacing = 60;
};

