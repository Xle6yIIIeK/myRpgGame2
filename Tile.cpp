#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(sf::Vector2f pos, float gridsize, const sf::IntRect& tetxture_rect,const  sf::Texture& texture)
{
	this->shape.setSize(sf::Vector2f(gridsize, gridsize));
	this->shape.setPosition(sf::Vector2f(pos));
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(tetxture_rect);

};

Tile::~Tile()
{

}

void Tile::update()
{

}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}