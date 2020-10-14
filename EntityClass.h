#ifndef ENTITYCLASS_H
#define ENTITYCLASS_H

#include "AnimatioComponent.h"
#include "AttributeComponent.h"
#include "HitBoxComponent.h"
#include "MovementComponents.h"
class MovementComponent;

class EntityClass
{
private:
	void initVariables();

protected:
	sf::Sprite sprite;
		  
	HitBoxComponent* hitboxcomponent;
	AnimationComponent* anmationcomponent;
	MovementComponent* movementcomponent;
	AttributeComponent* attributeComponent;
public:
	//Constructor Class
	EntityClass();

	//Destructor Class
	virtual ~EntityClass();


	//set texture
	//upload from file your textute sheet, and move to animation component
	void setTexture(sf::Texture& texture);

	//Create hitbox component
	//sf::Sprite& sprite - get sprite  
	//float offset_x, float offset_y - setup offset hitbox to sprite
	//float width, float height - setup size hitbox 
	void createHitBoxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);

	//Create aovement component
	//Float MaximumSpeed - Maximum movement speed per Second
	//Float Acceleration - Acceleration add vaule to MaxSpeed
	//Float deceleration - Deceleration remove valuse from MaxSpeed
	void createMovementComponent(const float maxSpeed, const float acceleration, const float deceleration);

	//Create animation component
	//Send Texture Sheet to Entity
	void createAnimationComponent(sf::Texture& texture_sheet);

	//Create attribute component
	void createAttributeComponent();

	//Virtual setup position Enity
	//const float x - setup X pos
	//const float y - setup Y pos
	virtual void setPosition(const float x, const float y);

	//Virtual move  Entity
	//const float dir_x - set direction to move = -1, 1
	//const float dir_y - set direction to move = -1, 1
	//const float &dt - update from to time
	virtual void move(const float dir_x, const float dir_y, const float& dt);

	virtual sf::Vector2f getPos() const;

	//Virtual update Entity
	//const float &dt - update from to time
	virtual void update(const float& dt);

	//Virtual render Entity
	//sf::RenderTarget& target - render Entity how a target to draw
	virtual void render(sf::RenderTarget& target);
};


#endif // !ENTITYCLASS_H