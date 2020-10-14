#include "PlayerClass.h"
//Initializer functions
void PlayerClass::initVariables()
{
	this->attack = false;
}

void PlayerClass::initComponents()
{
}

//Constructors / Destructors																							
PlayerClass::PlayerClass(float x, float y, sf::Texture& texture_sheet)
{
	this->setPosition(x, y);

	this->createHitBoxComponent(this->sprite, 0, 0, 64, 64);
	this->createMovementComponent(300.f, 60.f, 12.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent();

	this->anmationcomponent->addAnimation("IDLE", 80.f, 0, 0, 3, 0, 28, 36);
	this->anmationcomponent->addAnimation("WALK", 40.f, 0, 1, 16, 1, 28, 36);
	this->anmationcomponent->addAnimation("ATTACK", 10.f, 0, 1, 15, 1, 32, 32);
}

PlayerClass::~PlayerClass()
{

}
//Functions
void PlayerClass::updateAttack()
{

}

void PlayerClass::updateAnimation(const float& dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->attack = true;
	}
	if (this->attack)
	{
		//check origin on direction
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(0, 0);
		}
		else
		{

		}
		if (this->anmationcomponent->play("ATTACK", dt, true))
			this->attack = false;
	}
	if (this->movementcomponent->getState(IDLE))
	{
		this->sprite.setOrigin(0, 0);
		this->sprite.setScale(2.f, 2.f);
		this->anmationcomponent->play("IDLE", dt, 0);
	}
	else if (this->movementcomponent->getState(MOVELEFT))
	{
			this->sprite.setOrigin(28, 0);
			this->sprite.setScale(-2.0f, 2.0f);	
		this->anmationcomponent->play("WALK", dt, 0);
	}
	else if (this->movementcomponent->getState(MOVERIGHT))														  
	{	
			this->sprite.setOrigin(0, 0);
			this->sprite.setScale(2.0f, 2.0f);
		this->anmationcomponent->play("WALK", dt, 0);
	}
	else if (this->movementcomponent->getState(MOVEUP))
	{

	}
	else if (this->movementcomponent->getState(MOVEDOWN))
	{

	}
}

void PlayerClass::updateAttributes()
{
	this->attributeComponent->updateAtr();
}

void PlayerClass::update(const float& dt)
{
	this->movementcomponent->update(dt);
	this->updateAttack();
	this->updateAnimation(dt);
	this->updateAttributes();

	this->hitboxcomponent->update();
}
