#ifndef SETTINGSTATECLASS_H
#define SETTINGSTATECLASS_H
#include "Path.h"
#include "StateClass.h"
class SettingState:
	public State
{
private:
	//variables
	sf::RectangleShape backgoundShape;
	sf::Texture backgroundTexture;

	std::map<std::string, gui::ButtonClass*> button;
	std::map<std::string, gui::DropList*> dropList;

	std::vector<sf::VideoMode> videomode;


	void initVariables();
	void initKeybinds();
	void initBackground();
	void initGUI();

public:

	SettingState(StateData* state_data);
	virtual ~SettingState();
	
	//Functions
	void updateInput(const float& dt);
	void updateGUI(const float& dt);
	void update(const float& dt);

	void renderGUI(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
	//Accsesors

};


#endif // !SETTINGSTATECLASS_H
