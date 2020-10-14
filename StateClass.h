#ifndef STATE_H
#define STATE_H


#include "stdafx.h"
#include "Setting.h"
#include "GUI.h"

class GraphicsSettings;
class State;

class StateData
{
public:
	StateData() {};

	//Variables
	float gridSize;
	bool pause;
	sf::RenderWindow* window;
	GraphicsSettings* settings;
	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;
	sf::Font GlobalFont;
	bool debugMode_stateData;
};
class State
{
private:
protected:
	sf::RenderWindow* window;
	StateData* stateData;
	std::stack<State*>* states;

	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	sf::Font font;

	bool quit;
	bool paused;
	float keytime;
	float keytimeMax;
	float gridSize;
	bool debugMode_state;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;

	//Resources
	std::map<std::string, sf::Texture> textures;

	//Functions
	virtual void initKeybinds() = 0;

public:
	State(StateData* state_data);
	virtual ~State();

	//Accessors
	const bool getQuit() const;
	virtual const bool getKeytime();
	const bool getPause();
	const bool getDebugMode();

	//Functions	
	void endState(); 
	void pauseState();						  
	void unpauseState();
	
	virtual void updateMousePositions(sf::View* view = NULL);
	virtual void updateKeytime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};
#endif