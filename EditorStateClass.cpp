#include "EditorStateClass.h"

void EditorStateClass::initVariables()
{
	this->textureRect = sf::IntRect(
		0, 0, 
		static_cast<int>( this->stateData->gridSize),
		static_cast<int>(this->stateData->gridSize)
	);

}


void EditorStateClass::initKeybinds()
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

void EditorStateClass::initTileMap(float gridsize,sf::Vector2u size)
{
	this->tileMap = new TileMap(gridsize,size);
}

void EditorStateClass::initDebugMouse()
{
	if (this->getDebugMode())
	{
		this->mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
		this->mouseText.setFont(this->font);
		this->mouseText.setCharacterSize(16);
		this->mouseText.setFillColor(sf::Color::White);
	}
}

void EditorStateClass::initButtons()
{
	this->button["SAVE"] = new gui::ButtonClass(
		sf::Vector2f(
			this->window->getSize().x - 40.f,
			this->window->getSize().y - 25.f),
		sf::Vector2f(40, 25),
		&this->font, "Save", 23,
		sf::Color(180, 180, 180), sf::Color(220, 220, 220), sf::Color(200, 200, 200),
		sf::Color(80, 80, 80), sf::Color(100, 100, 100), sf::Color(70, 70, 70)
		);
}

void EditorStateClass::initGui()
{
	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(sf::Color::Transparent);
	this->selectorRect.setOutlineColor(sf::Color::Green);
	this->selectorRect.setOutlineThickness(2.f);

}

void EditorStateClass::initPause()
{
	this->pausemenu = new PauseMenuClass(*this->window, this->font);

	this->pausemenu->createButton("QUIT", this->window->getSize().y - (this->window->getSize().y / 7), "Quit");
}

EditorStateClass::EditorStateClass(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initKeybinds();
	this->initButtons();
	this->initGui();
	this->initTileMap(this->gridSize,sf::Vector2u(20,20));
	this->initPause();

	if (this->getDebugMode())
		this->initDebugMouse();
}

EditorStateClass::~EditorStateClass()
{
	for (auto it = this->button.begin(); it != this->button.end(); ++it)
		delete it->second;

	delete this->pausemenu;
	delete this->tileMap;
}

//Functions
void EditorStateClass::updateInput(const float& dt)
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

void EditorStateClass::updateInputEditor(const float& dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime())
		this->tileMap->addTile(sf::Vector3f(this->mousePosGrid.x, this->mousePosGrid.y, 0),this->textureRect);

	if(sf::Mouse::isButtonPressed(sf::Mouse::Right)&&this->getKeytime())
		this->tileMap->removeTile(sf::Vector3f(this->mousePosGrid.x, this->mousePosGrid.y, 0));
};

void EditorStateClass::updateButtons()
{
	for (auto& it : this->button)
		it.second->update(this->mousePosView);
}

void EditorStateClass::updateGui()
{
	this->selectorRect.setPosition(this->mousePosGrid.x*this->gridSize, this->mousePosGrid.y * this->gridSize);
}

void EditorStateClass::updatePauseButton()
{
	if (this->pausemenu->Pressed("QUIT"))
		this->endState();
}

void EditorStateClass::updateMouseText()
{
	this->ss.str("");
	this->ss <<
		"Mouse Pos: " << this->mousePosView.x << " " << this->mousePosView.y << "\n" <<
		"Select Textute: " << this->textureRect.left << "x" << this->textureRect.top;

	this->mouseText.setString(this->ss.str());
	this->mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
}

void EditorStateClass::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused)		 //unpause update
	{
		this->updateInputEditor(dt);
		this->updateGui();
		this->updateButtons();

		if(this->getDebugMode())
			this->updateMouseText();
	}
	else	   //pause update
	{
		this->pausemenu->update(this->mousePosView);
		this->updatePauseButton();

		if (this->getDebugMode())
			this->updateMouseText();
	}

}

void EditorStateClass::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->button)
	{
		it.second->render(target);
	}
}

void EditorStateClass::renderGui(sf::RenderTarget& target)
{
	target.draw(this->selectorRect);
}

void EditorStateClass::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	switch (this->paused)
	{
	case true:
		this->tileMap->render(*target);
		this->renderGui(*target);
		this->pausemenu->render(*target);
		if (this->getDebugMode())
			target->draw(this->mouseText);
		break;
	case false:
		this->tileMap->render(*target);
		this->renderGui(*target);
		this->renderButtons(*target);
		if (this->getDebugMode())
			target->draw(this->mouseText);
		break;
	}
}

