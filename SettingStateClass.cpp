#include "SettingStateClass.h"

void SettingState::initVariables()
{
	this->videomode = sf::VideoMode::getFullscreenModes();
}

void SettingState::initKeybinds()
{
	std::fstream ifs(gameKeys);

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";
		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void SettingState::initBackground()
{
	this->backgoundShape.setSize(
		sf::Vector2f(
			this->window->getSize().x,
			this->window->getSize().y
			)
		);

	if (!this->backgroundTexture.loadFromFile("Resourses/images/backGround.png"))
	{
		throw "ERROR::SettingState::initBackground Resourses/images/backGround.png Can`t do load";
	}

	this->backgoundShape.setTexture(&this->backgroundTexture);
}

void SettingState::initGUI()
{
	this->button["BACK"] = new gui::ButtonClass(
		sf::Vector2f(
			this->window->getSize().x - 240.f,
			this->window->getSize().y - 50.f),
		sf::Vector2f(120, 50),
		&this->font, "Back", 30,
		sf::Color(180, 180, 180), sf::Color(220, 220, 220), sf::Color(200, 200, 200),
		sf::Color(80, 80, 80), sf::Color(100, 100, 100), sf::Color(70, 70, 70)
		);

	this->button["APPLY_BUTTON"] = new gui::ButtonClass(
		sf::Vector2f(
			this->window->getSize().x - 360.f,
			this->window->getSize().y - 50.f),
		sf::Vector2f(120, 50),
		&this->font, "Apply", 30,
		sf::Color(180, 180, 180), sf::Color(220, 220, 220), sf::Color(200, 200, 200),
		sf::Color(80, 80, 80), sf::Color(100, 100, 100), sf::Color(70, 70, 70)
		);

	std::vector<std::string> videomode_str;

	for (auto& i : this->videomode)
	{
		videomode_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}


	this->dropList["Resolution"] = new gui::DropList(
		sf::Vector2f(this->window->getSize().x / 32, this->window->getSize().y / 18), sf::Vector2f(200, 28),
		&this->font, videomode_str.data(), videomode_str.size(), 0, false
		);
};



SettingState::SettingState(StateData* state_data):
	State(state_data)
{
	this->initVariables();
	this->initKeybinds();
	this->initBackground();
	this->initGUI();
}

SettingState::~SettingState()
{
	auto it = this->button.begin();
	for (it = this->button.begin(); it != this->button.end(); ++it)
	{
		delete it->second;
	}

	auto i = this->dropList.begin();
	for (i = this->dropList.begin(); i != this->dropList.end(); ++i)
	{
		delete i->second;
	}
}

//Functions
void SettingState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

void SettingState::updateGUI(const float& dt)
{
	//Update all GUI elements it the state and handle their functionaly
	//Buttons update
	for (auto& it : this->button)
	{
		it.second->update(this->mousePosView);
	}
	//Updare Drop list and their elements
	for (auto& it : this->dropList)
	{
		it.second->update(this->mousePosView, dt);
	}
	//Button for exit from this state
	if (this->button["BACK"]->isPressed())
	{
		this->endState();
	}
	////////Apply select setting button///////////////
	if (this->button["APPLY_BUTTON"]->isPressed())
	{
		this->window->create(this->videomode[this->dropList["Resolution"]->getActiveElementID()], "test", sf::Style::Default);
		//this->stateData->settings->saveToFile(settingWindowPath);
	}
}



void SettingState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateGUI(dt);
}

void SettingState::renderGUI(sf::RenderTarget& target)
{
	for (auto& ib : this->button)
		ib.second->render(target);

	for (auto& it : this->dropList)
		it.second->render(target);
}

void SettingState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->stateData->window;

	target->draw(this->backgoundShape);

	this->renderGUI(*target);
}

//Accsesors