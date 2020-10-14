#ifndef CORE_H
#define CORE_H
#include "Path.h"
#include "MainMenuClass.h"

class CORE
{
private:
	sf::RenderWindow* window;
	GraphicsSettings setting;
	StateData stateData;
	sf::Event sfEvent;
	float gridSize;

	sf::Clock clock;
	sf::Font coreFont;

	float dt;
	bool debug;

	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;

	void initVariables();

	void initWindow();
	void initGraphics();
	void initKeys();
	void initStateData();
	void initState();
	void initFount();

public:
	CORE();
	virtual ~CORE();

	void updateTime();
	void updateSFML();
	void update();

	void render();

	void run();

};
#endif