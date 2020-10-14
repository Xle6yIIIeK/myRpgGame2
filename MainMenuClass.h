#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H
#include "Path.h"
#include "StateClass.h"
#include "NetCore.h"

class MainMenuClass
	:public State, public NetCore
{
private:
	//variables
	sf::RectangleShape backgoundshape;
	sf::Texture backgroundTexture;
	sf::Music music;

	std::map<std::string, gui::ButtonClass*> button;

	void initVariables();
	void initKeybinds();	
	void initBackground();
	void initButtons();
	void initMusic();
public:
	MainMenuClass(StateData* state_data);
	virtual ~MainMenuClass();


	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target=NULL);

};

#endif MAINMENUSTATE_H