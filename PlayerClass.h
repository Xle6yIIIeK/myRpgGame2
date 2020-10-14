#ifndef PLAYERCLASS_H
#define PLAYERCLASS_H

#include "EntityClass.h"
class PlayerClass :
	public EntityClass
{
private:
	//variables
	bool attack;


	//init Functions
	void initVariables();
	void initComponents();

public:
	//CONST - DEST
	PlayerClass(float x, float y, sf::Texture& texture_sheet);
	virtual ~PlayerClass();

	//Functions
	void updateAttack();
	void updateAnimation(const float& dt);
	void updateAttributes();
	virtual void update(const float& dt);
};
#endif // !PLAYERCLASS_H