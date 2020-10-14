#include "gui.h"

gui::ButtonClass::ButtonClass(
	sf::Vector2f pos, sf::Vector2f size,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_Color, sf::Color hover_color, sf::Color active_color,
	sf::Color outline_idle_Color, sf::Color outline_hover_color, sf::Color outline_active_color,
	short unsigned id)
{
	this->buttonstate = BUTTONT_IDLE;

	this->buttonShape.setPosition(sf::Vector2f(pos));
	this->buttonShape.setSize(sf::Vector2f(size));
	this->buttonShape.setFillColor(idle_Color);
	this->buttonShape.setOutlineThickness(3.f);
	this->buttonShape.setOutlineColor(outline_idle_Color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setCharacterSize(character_size);
	this->text.setFillColor(idle_Color);
	this->text.setPosition(
		this->buttonShape.getPosition().x + (this->buttonShape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->buttonShape.getPosition().y
		);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_Color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->outLineIdleColor = outline_idle_Color;
	this->outLineHoverColor = outline_hover_color;
	this->outLineActiveColor = outline_active_color;

	this->id = id;
}

gui::ButtonClass::~ButtonClass()
{

}

const std::string gui::ButtonClass::getText() const
{
	return this->text.getString();
}

const short unsigned gui::ButtonClass::getId() const
{
	return this->id;
}

const bool gui::ButtonClass::isPressed() const
{
	if (this->buttonstate == BUTTON_ACTIVE)
		return true;

	return false;
}

//Modefires
void gui::ButtonClass::setText(std::string textButton)
{
	this->text.setString(textButton);
}

void gui::ButtonClass::setId(const short unsigned id)
{
	this->id = id;
}

void gui::ButtonClass::update(const sf::Vector2f& mousepos)
{
	this->isPressed();

	this->buttonstate = BUTTONT_IDLE;

	if (this->buttonShape.getGlobalBounds().contains(mousepos))
	{
		this->buttonstate = BUTTONT_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonstate = BUTTON_ACTIVE;
		}
	}

	switch (this->buttonstate)
	{
	case BUTTONT_IDLE:
		this->buttonShape.setOutlineColor(this->outLineIdleColor);
		this->buttonShape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		break;

	case BUTTONT_HOVER:
		this->buttonShape.setOutlineColor(this->outLineHoverColor);
		this->buttonShape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		break;

	case BUTTON_ACTIVE:
		this->buttonShape.setOutlineColor(this->outLineActiveColor);
		this->buttonShape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		break;

	default:
		this->buttonShape.setOutlineColor(sf::Color::Blue);
		this->buttonShape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Green);
		break;
	}
}

void gui::ButtonClass::render(sf::RenderTarget& target)
{
	target.draw(this->buttonShape);
	target.draw(this->text);
}

gui::DropList::DropList(sf::Vector2f pos, sf::Vector2f size, sf::Font* font, std::string list[], unsigned numElement, unsigned defauld_index, bool drawdown)
	:showList(false), KeyTimeMax(10.f), keyTime(0.f)
{
	this->activeElement = new ButtonClass(
		sf::Vector2f(pos), sf::Vector2f(size),
		font, list[defauld_index], 25,
		sf::Color(180, 180, 180), sf::Color(255, 255, 255), sf::Color(220, 220, 220),
		sf::Color(80, 80, 80), sf::Color(100, 100, 100), sf::Color(70, 70, 70),
		sf::Color(20, 20, 80), sf::Color(20, 20, 100), sf::Color(30, 30, 120));

	for (size_t it = 0; it < numElement; it++)
	{
		if (!drawdown)
			this->list.push_back(
				new gui::ButtonClass(
					sf::Vector2f(
						sf::Vector2f(pos).x,
						sf::Vector2f(pos).y + ((it + 1) * sf::Vector2f(size).y)
						),
					sf::Vector2f(size),
					font, list[it], 20,
					sf::Color(180, 180, 180), sf::Color(220, 220, 220), sf::Color(200, 200, 200),
					sf::Color(80, 80, 80), sf::Color(100, 100, 100), sf::Color(70, 70, 70),
					sf::Color(120, 80, 80), sf::Color(120, 100, 100), sf::Color(100, 70, 70),
					it
					)
				);
		else
			this->list.push_back(
				new gui::ButtonClass(
					sf::Vector2f(
						sf::Vector2f(pos).x,
						sf::Vector2f(pos).y - ((it + 1) * sf::Vector2f(size).y)
						),
					sf::Vector2f(size),
					font, list[it], 20,
					sf::Color(180, 180, 180), sf::Color(220, 220, 220), sf::Color(200, 200, 200),
					sf::Color(80, 80, 80), sf::Color(100, 100, 100), sf::Color(70, 70, 70),
					sf::Color(120, 80, 80), sf::Color(120, 100, 100), sf::Color(100, 70, 70),
					it
					)
				);
	}
}
 
gui::DropList::~DropList()
{
	delete this->activeElement;
	for (size_t it = 0; it < this->list.size(); it++)
	{
		delete this->list[it];
	}
}

const bool gui::DropList::getKeyTime()
{
	if (this->keyTime >= KeyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}
	return true;
}

const unsigned short& gui::DropList::getActiveElementID() const
{
	return this->activeElement->getId();
}

void gui::DropList::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->KeyTimeMax)
	{
		this->keyTime = this->keyTime + 10.f * dt;
	}
}

void gui::DropList::update(const sf::Vector2f& mousepos, const float& dt)
{
	this->updateKeyTime(dt);

	this->activeElement->update(mousepos);

	if (this->activeElement->isPressed() && this->getKeyTime())
	{
		if (this->showList)
			this->showList = false;
		else
			this->showList = true;
	}

	if (this->showList)
	{
		for (auto& it : this->list)
		{
			it->update(mousepos);

			if (it->isPressed()&&this->getKeyTime())
			{
				this->showList = false;
				this->activeElement->setText(it->getText());
				this->activeElement->setId(it->getId());
			}
		}
	};
}

void gui::DropList::render(sf::RenderTarget& targer)
{
	activeElement->render(targer);

	if (this->showList)
	{
		for (auto& it : this->list)
		{
			it->render(targer);
		}
	};
}

gui::TextBox::TextBox(sf::Vector2f pos, sf::Vector2f size, sf::Font* font, unsigned character_size, std::string text,std::string data)
{
	this->textShape.setPosition(pos);
		this->textShape.setSize(size);
		this->textShape.setFillColor(sf::Color(20,20,20,50));

		this->text.setFont(*font);
		this->text.setString(text);
		this->text.setCharacterSize(character_size);
		this->text.setFillColor(sf::Color::White);

		this->text.setPosition(
			this->textShape.getPosition().x,
			this->textShape.getPosition().y 
		);

		this->data.setFont(*font);
		this->data.setString(data);
		this->data.setCharacterSize(character_size);
		this->data.setFillColor(sf::Color::White);

		this->data.setPosition(
			this->textShape.getPosition().x+5.f+this->text.getGlobalBounds().width,
			this->textShape.getPosition().y
			);
}

gui::TextBox::~TextBox()
{

}

void gui::TextBox::update(int data)
{
	this->data.setString(std::to_string(data));
}

void gui::TextBox::renderText(sf::RenderTarget& target)
{
	target.draw(this->textShape);
	target.draw(this->text);
	target.draw(this->data);
}
