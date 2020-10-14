#include "AttributeComponent.h"

void AttributeComponent::initState()
{
	this->live = true;

	this->level = 1;
	this->curectexp = 0;
	this->needexp = 100 + (this->level + (this->level * 5)* this->level *6) + 1;

	this->agility = 5;
	this->strength = 5;
	this->intellect = 5;

	this->health = this->healthMax = this->strength * 8;
	this->mana = this->manaMax = this->intellect * 4 + 5;

}

AttributeComponent::AttributeComponent()
{
	this->initState();
}

AttributeComponent::~AttributeComponent()
{			 
}

bool AttributeComponent::getLive()
{
	return this->live;
}

void AttributeComponent::lvlup()
{
	if (this->curectexp>=this->needexp)
	{
		this->level++;
		this->curectexp = 0;
		this->needexp = 100 + (this->level + (this->level * 5) * this->level * 6) + 1;

		this->agility++;
		this->strength++;
		this->intellect++;

		this->healthMax = this->strength * 8;
		this->manaMax = this->intellect * 4 + 5;
	}
}

void AttributeComponent::updateAtr()
{
	if (this->live==true)
	{
		this->lvlup();
	}
}

