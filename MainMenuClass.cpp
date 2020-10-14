#include "MainMenuClass.h"
#include "GameStateClass.h"
#include "EditorStateClass.h"
#include "SettingStateClass.h"

void MainMenuClass::initVariables()
{

}

void MainMenuClass::initKeybinds()
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

void MainMenuClass::initBackground()
{
	this->backgoundshape.setSize(
		sf::Vector2f(
			this->window->getSize().x,
			this->window->getSize().y
			)
		);

	if (!this->backgroundTexture.loadFromFile(mainmenuBackgroundPath))
	{
		throw "ERROR::MainMenuClass::initBackground Resourses/images/backGround.png Can`t do load";
	}

	this->backgoundshape.setTexture(&this->backgroundTexture);
}

void MainMenuClass::initButtons()
{
	this->button["GAME_STATE_BUTTON"] = new gui::ButtonClass(
		sf::Vector2f(
			this->window->getSize().x - 120,
			this->window->getSize().y - 250),
		sf::Vector2f(120.f, 50.f),
		&this->font, "New Game", 30,
		sf::Color(180, 180, 180), sf::Color(220, 220, 220), sf::Color(200, 200, 200),
		sf::Color(80, 80, 80), sf::Color(100, 100, 100), sf::Color(70, 70, 70));

	this->button["EDITOR_BUTTON"] = new gui::ButtonClass(
		sf::Vector2f(
			this->window->getSize().x - 120,
			this->window->getSize().y - 200),
		sf::Vector2f(120.f, 50.f),
		&this->font, "Editor", 30,
		sf::Color(180, 180, 180), sf::Color(220, 220, 220), sf::Color(200, 200, 200),
		sf::Color(80, 80, 80), sf::Color(100, 100, 100), sf::Color(70, 70, 70));

	this->button["SETTING_BUTTON"] = new gui::ButtonClass(
		sf::Vector2f(
			this->window->getSize().x - 120,
			this->window->getSize().y - 150),
		sf::Vector2f(120, 50),
		&this->font, "Setting", 30,
		sf::Color(180, 180, 180), sf::Color(220, 220, 220), sf::Color(200, 200, 200),
		sf::Color(80, 80, 80), sf::Color(100, 100, 100), sf::Color(70, 70, 70));

	this->button["EXIT_BUTTON"] = new gui::ButtonClass(
		sf::Vector2f(this->window->getSize().x - 120, this->window->getSize().y - 50),
		sf::Vector2f(120, 50),
		&this->font, "Exit", 30,
		sf::Color(180, 180, 180), sf::Color(220, 220, 220), sf::Color(200, 200, 200),
		sf::Color(80, 80, 80), sf::Color(100, 100, 100), sf::Color(70, 70, 70)
		);
}

void MainMenuClass::initMusic()
{
	this->music.openFromFile("Resourses/Music/mainmenumusic.flac");
	this->music.play();
	this->music.setVolume(10);
}

MainMenuClass::MainMenuClass(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initKeybinds();
	this->initBackground();
	this->initButtons();
	this->initMusic();
}

MainMenuClass::~MainMenuClass()
{
	auto it = this->button.begin();
	for (it = this->button.begin(); it != this->button.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuClass::updateInput(const float& dt)
{
}

void MainMenuClass::updateButtons()
{
	for (auto& it : this->button)
	{
		it.second->update(this->mousePosView);
	}
	if (this->button["GAME_STATE_BUTTON"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
	}
	if (this->button["SETTING_BUTTON"]->isPressed())
	{
		this->states->push(new SettingState(this->stateData));
	}
	if (this->button["EDITOR_BUTTON"]->isPressed())
	{
		this->states->push(new EditorStateClass(this->stateData));
	}
	if (this->button["EXIT_BUTTON"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuClass::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();

	this->sendPack(dt);
}


void MainMenuClass::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->button)
	{
		it.second->render(target);
	}
}

void MainMenuClass::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->backgoundshape);
	this->renderButtons(*target);
}
