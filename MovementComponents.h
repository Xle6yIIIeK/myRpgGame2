#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H
#include "stdafx.h"

enum movementState { IDLE = 0, MOVING, MOVELEFT, MOVERIGHT, MOVEUP, MOVEDOWN }; 

class MovementComponent
{
private:
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;

	//Initializer functions

public:
	MovementComponent(sf::Sprite& sprite,
		float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessors
	const float& getMaxVelocity() const;
	const sf::Vector2f& getVelocity() const;

	//Functions
	const bool getState(const short unsigned state) const;

	void move(const float dir_x, const float dir_y, const float& dt);
	void update(const float& dt);
};
#endif