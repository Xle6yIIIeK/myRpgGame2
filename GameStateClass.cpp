#include "GameStateClass.h"

void GameState::initVariavles()
{
}

void GameState::initKeybinds()
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

void GameState::initTexture()
{
	this->textures["sheet"].loadFromFile("Resourses/images/Entitys/CustomSet.png");
}

void GameState::initPauseMenu()
{
	this->pMenu = new PauseMenuClass(*this->window, this->font);

	this->pMenu->createButton("QUIT", this->window->getSize().y-(this->window->getSize().y/7), "Quit");
}

void GameState::initPlayer()
{
	this->player = new PlayerClass(0, 0, this->textures["sheet"]);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, sf::Vector2u(20,20));
}

GameState::GameState(StateData* state_data)
	:State(state_data)
{
	this->initVariavles();
	this->initKeybinds();
	this->initPauseMenu();
	this->initTileMap();
	this->initTexture();
	this->initPlayer();
}

GameState::~GameState()
{
	delete this->tileMap;
	delete this->player;
	delete this->pMenu;
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		switch (this->paused)
		{
		case true:
			this->unpauseState();
			break;
		case false:
			this->pauseState();
			break;
		}
	}
}

void GameState::updateButtons()
{
	if (this->pMenu->Pressed("QUIT"))
	{
		this->sys.save(gamesavePath, &this->player->getPos());

		this->endState();
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(0.f, 1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	
}

void GameState::update(const float &dt)
{
	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateInput(dt);
	
	if (!this->paused)		 //unpause update
	{
		this->updatePlayerInput(dt);
		this->tileMap->update();
		this->player->update(dt);
	}
	else	   //pause update
	{
		this->pMenu->update(this->mousePosView);
		this->updateButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	switch (this->paused)
	{														
	case true:
		this->tileMap->render(*target);
		this->player->render(*target);
		this->pMenu->render(*target);
		break;
	case false:
		this->tileMap->render(*target);
		this->player->render(*target);
		break;
	}
}