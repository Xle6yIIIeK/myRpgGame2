#ifndef HITBOXCOMPONENT
#define HITBOXCOMPONENT

#include "stdafx.h"
class HitBoxComponent
{
private:
	sf::RectangleShape hitBox;
	sf::Sprite& sprite;

	float offsetX;
	float offsetY;

public:
	/*
	Apply your sprite to size hitbox
	and offset_x, offset_y

	*/
	HitBoxComponent(sf::Sprite& sprite,
		float offset_x, float offset_y,
		float width, float height);
	virtual ~HitBoxComponent();

	 //func
	bool collision(const sf::FloatRect& floatRect);

	void update();
	void render(sf::RenderTarget& target);




};


#endif // !HITBOXCOMPONENT