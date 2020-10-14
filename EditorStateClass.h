#ifndef EDITORSTATECLASS_H
#define EDITORSTATECLASS_H
#include "Path.h"
#include "StateClass.h"
#include "PauseMenuClass.h"
#include "TileMap.h"

class EditorStateClass :
	public State
{
private:
	//variables
	PauseMenuClass* pausemenu;
	std::map<std::string, gui::ButtonClass*> button;
	TileMap* tileMap;

	sf::RectangleShape selectorRect;
	sf::IntRect textureRect;

	sf::Text mouseText;
	std::stringstream ss;

	void initVariables();
	void initKeybinds();
	void initPause();
	void initButtons();
	void initGui();
	void initTileMap(float gridSize, sf::Vector2u size);
	void initDebugMouse();

public:
	EditorStateClass(StateData* state_data);
	virtual ~EditorStateClass();


	void updateInput(const float& dt);
	void updateInputEditor(const float& dt);
	void updateButtons();
	void updateGui();
	void updatePauseButton();
	void update(const float& dt);
	void updateMouseText();
	void renderButtons(sf::RenderTarget& target);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);

};
#endif EDITORSTATECLASS_H