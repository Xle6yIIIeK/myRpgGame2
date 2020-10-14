#ifndef TILE_H
#define TILE_H
#include "stdafx.h"
class Tile
{
private:

protected:
	sf::RectangleShape shape;


public:
	Tile();
	Tile(sf::Vector2f pos, float gridsize,const sf::IntRect& tetxture_rect,const sf::Texture& texture);
	virtual ~Tile();

	void update();
	void render(sf::RenderTarget& target);
};

#endif // !TILE_H
