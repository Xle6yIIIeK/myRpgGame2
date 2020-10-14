#include "PauseMenuClass.h"

const bool PauseMenuClass::Pressed(const std::string key) 
{
	return this->buttons[key]->isPressed();
}

void PauseMenuClass::createButton(std::string key, const float y, std::string text)
{
	float wi = 120.f;
	float he = 50.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - wi/2.f;
	
	this->buttons[key] = new gui::ButtonClass(
		sf::Vector2f(x, y), sf::Vector2f(wi, he),
		&this->pFont, text, 30,
		sf::Color(180, 180, 180), sf::Color(220, 220, 220), sf::Color(200, 200, 200),
		sf::Color(80, 80, 80), sf::Color(100, 100, 100), sf::Color(70, 70, 70));
}

PauseMenuClass::PauseMenuClass(sf::RenderWindow& window, sf::Font& font)
	:pFont(font)
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x),
			static_cast<float>(window.getSize().y)
			)
		);

	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x) / 3.f,
			static_cast<float>(window.getSize().y) - 100.f
			)
		);

	this->container.setFillColor(sf::Color(30, 30, 30));
	this->container.setPosition(
		static_cast<float>(
			window.getSize().x) / 2.f - this->container.getSize().x / 2.f,
		50.f);

	this->menuText.setString("PAUSED");
	this->menuText.setCharacterSize(60);
	this->menuText.setFont(this->pFont);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setPosition(
		static_cast<float>(this->container.getPosition().x+this->container.getSize().x/2 - this->menuText.getGlobalBounds().width/2),
		static_cast<float>(this->container.getPosition().y+this->menuText.getGlobalBounds().height )
		);
}

PauseMenuClass::~PauseMenuClass()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}
																				 
std::map<std::string, gui::ButtonClass*>& PauseMenuClass::getButtons()
{
	return this->buttons;
}

//functions
void PauseMenuClass::update(sf::Vector2f& mousePos)
{
	
	for (auto& i : this->buttons)
	{
		i.second->update(mousePos);
	}
}

void PauseMenuClass::render(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(container);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
	target.draw(this->menuText);
}
