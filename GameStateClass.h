#ifndef GAMESTATE_H
#define GAMESTATE_H
//test
#include "FileSys.h"
#include "Path.h"

#include "StateClass.h"
#include "PlayerClass.h"
#include "PauseMenuClass.h"
#include "TileMap.h"
class GameState:
	public State
{
private:
	PauseMenuClass* pMenu;
	PlayerClass* player;
	TileMap* tileMap;
	void initVariavles();

	nvs::myFileSystem sys;

	void initKeybinds();
	void initTexture();
	void initPauseMenu();
	void initPlayer();
	void initTileMap();
public:
	GameState(StateData* state_data);
	virtual ~GameState();

	void updateInput(const float& dt);
	void updateButtons();
	void updatePlayerInput(const float& dt);
	void update(const float& dt);
																 
	void render(sf::RenderTarget* target);

};
#endif	