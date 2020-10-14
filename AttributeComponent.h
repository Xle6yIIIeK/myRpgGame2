#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H
#include "stdafx.h"

class AttributeComponent
{
private:
	bool live;

	unsigned short level;
	unsigned short curectexp;
	unsigned short needexp;

	unsigned short strength;
	unsigned short agility;
	unsigned short intellect;
	unsigned short health;
	unsigned short healthMax;
	unsigned short mana;
	unsigned short manaMax;

	void initState();

public:
	AttributeComponent();
	virtual ~AttributeComponent();

	bool getLive();

	void lvlup();
	void updateAtr();
};

#endif // !ATTRIBUTECOMPONENT_H
