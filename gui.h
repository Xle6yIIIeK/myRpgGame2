#ifndef GUI_I
#define GUI_I
#include "stdafx.h"

enum buttonState { BUTTONT_IDLE = 0, BUTTONT_HOVER, BUTTON_ACTIVE };

namespace gui
{
	class ButtonClass
	{
	private:
		short unsigned buttonstate;
		short unsigned id;

		sf::RectangleShape buttonShape;
		sf::Font* font;
		sf::Text text;

		sf::Color textIdleColor, textHoverColor, textActiveColor;
		sf::Color idleColor, hoverColor, activeColor;
		sf::Color outLineIdleColor, outLineHoverColor, outLineActiveColor;

	public:
		ButtonClass(
			sf::Vector2f pos, sf::Vector2f size,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_Color, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_Color=sf::Color::Transparent,
			sf::Color outline_hover_color = sf::Color::Transparent, 
			sf::Color outline_active_color = sf::Color::Transparent,
			short unsigned id=0);

		virtual ~ButtonClass();

		//Accses
		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned getId() const;
		//modifires
		void setText(std::string textButton);
		void setId(const short unsigned id);

		//func
		void update(const sf::Vector2f& mousepos);
		void render(sf::RenderTarget& targer);
	};

	class DropList
	{
	private:
		float keyTime, KeyTimeMax;
		ButtonClass* activeElement;
		std::vector<gui::ButtonClass*> list;
		bool showList;

	public:
		DropList(sf::Vector2f pos, sf::Vector2f size,
			sf::Font* dlfont, std::string list[],
			unsigned numElement, unsigned defauld_index = 0, bool drawdown=true);

		virtual ~DropList();

		const bool getKeyTime();
		const unsigned short& getActiveElementID() const;
		void updateKeyTime(const float& dt);
		void update(const sf::Vector2f& mousepos, const float& dt);
		void render(sf::RenderTarget& targer);
	};

	class TextBox
	{
	private:
		sf::RectangleShape textShape;
		sf::Text text, data;
	public:
		TextBox(sf::Vector2f pos, sf::Vector2f size,
			sf::Font* font, unsigned character_size,
			std::string text, std::string data);
		virtual ~TextBox();

		void update(int data);
		void renderText(sf::RenderTarget& target);

	};
};
#endif // !GUI_I