#include "EntityClass.h"

void EntityClass::initVariables()
{
	this->movementcomponent = NULL;
	this->anmationcomponent = NULL;
	this->hitboxcomponent = NULL;
}

EntityClass::EntityClass()
{
	this->initVariables();
}

EntityClass::~EntityClass()
{
	delete this->movementcomponent;
	delete this->anmationcomponent;
	delete this->hitboxcomponent;
}

void EntityClass::createHitBoxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
{
	this->hitboxcomponent = new HitBoxComponent(sprite, offset_x, offset_y, width, height);
}

void EntityClass::createMovementComponent(const float maxSpeed, const float acceleration, const float deceleration)
{
	this->movementcomponent = new MovementComponent(this->sprite, maxSpeed, acceleration, deceleration);
}

void EntityClass::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->anmationcomponent = new AnimationComponent(this->sprite, texture_sheet);
}

void EntityClass::createAttributeComponent()
{
	this->attributeComponent = new AttributeComponent();
}

void EntityClass::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void EntityClass::setPosition(const float x, const float y)
{
		this->sprite.setPosition(x, y);
}

void EntityClass::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementcomponent)
	{
		this->movementcomponent->move(dir_x, dir_y, dt); //Sets velocity
	}
}

sf::Vector2f EntityClass::getPos() const
{
	return this->sprite.getPosition();
}

void EntityClass::update(const float& dt)
{

}

void EntityClass::render(sf::RenderTarget& target)
{
		if (this->hitboxcomponent)
			this->hitboxcomponent->render(target);
		target.draw(this->sprite);
}
						     