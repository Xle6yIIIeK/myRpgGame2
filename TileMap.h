#ifndef TILEMAP_H
#define TILEMAP_H
#include "TexturesPath.h"
#include "Tile.h"

class TileMap
{
private:
	float gridSize;
	float layer;
	sf::Vector2u mapSize;
	std::vector< std::vector < std::vector <Tile*>>> map;
	sf::Texture textrureSheet;
public:
	TileMap(float gridsize, sf::Vector2u size);
	virtual ~TileMap();

	void update();
	void render(sf::RenderTarget& target);

	void addTile(sf::Vector3f pos, const sf::IntRect& textute_rect);
	void removeTile(sf::Vector3f pos);
};
#endif  TILEMAP_H