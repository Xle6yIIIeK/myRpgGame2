#ifndef PAUSEMENU_H
#define PAUSEMENU_H
#include "stdafx.h"
#include "GUI.h"

class PauseMenuClass
{
private:
	sf::Text menuText;
	sf::Font pFont;
	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::ButtonClass*> buttons;
public:
	PauseMenuClass(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenuClass();

	std::map<std::string, gui::ButtonClass*>& getButtons();

	const bool Pressed(const std::string key);
	void createButton(std::string key, const float y, std::string text);
	void update(sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);
};
#endif // !PAUSEMENU_H