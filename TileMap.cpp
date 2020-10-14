#include "TileMap.h"

TileMap::TileMap(float gridsize, sf::Vector2u size)
{
	this->gridSize = gridsize;
	this->layer = 1;
	this->mapSize.x = size.x;
	this->mapSize.y = size.y;
	this->textrureSheet.loadFromFile(textureSheet1);


	this->map.resize(this->mapSize.x, std::vector<std::vector<Tile*>>());
	for (size_t x = 0; x < this->mapSize.x; x++)
	{
		for (size_t y = 0; y < this->mapSize.y; y++)
		{
			this->map[x].resize(this->mapSize.y, std::vector<Tile*>());

			for (size_t z = 0; z < this->layer; z++)
			{
				this->map[x][y].resize(this->layer,NULL);
			}
		}
	}
}

TileMap::~TileMap()
{
	for (size_t x = 0; x < this->mapSize.x; x++)
		for (size_t y = 0; y < this->mapSize.y; y++)
			for (size_t z = 0; z < this->layer; z++)
				delete this->map[x][y][z];
}


void TileMap::addTile(sf::Vector3f pos,const sf::IntRect& textute_rect )
{
	if (pos.x < this->mapSize.x && pos.x >= 0 &&
		pos.y < this->mapSize.y && pos.y >= 0 &&
		pos.z <= this->layer && pos.z >= 0)
	{
		if (this->map[pos.x][pos.y][pos.z] == NULL)
		{
			this->map[pos.x][pos.y][pos.z] = new Tile(
				sf::Vector2f(
					pos.x * this->gridSize,
					pos.y * this->gridSize),
				this->gridSize,
				textute_rect, this->textrureSheet);
		}
	}
}

void TileMap::removeTile(sf::Vector3f pos)
{
	if (pos.x < this->mapSize.x && pos.x >= 0 &&
		pos.y < this->mapSize.y && pos.y >= 0 &&
		pos.z <= this->layer && pos.z >= 0)
	{
		if (this->map[pos.x][pos.y][pos.z] != NULL)
		{
			delete this->map[pos.x][pos.y][pos.z];
			this->map[pos.x][pos.y][pos.z] = NULL;
		}
	}
}

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto* z : y)
			{
				if(z!=NULL)
				z->render(target);
			}
		}
	}
}

