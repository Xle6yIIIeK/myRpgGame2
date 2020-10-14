#include "TileMap.h"

int Object::GetPropertyInt(std::string name)					//возвращаем номер свойства в нашем списке
{
	return atoi(properties[name].c_str());
}

float Object::GetPropertyFloat(std::string name)
{
	return strtod(properties[name].c_str(), NULL);
}

std::string Object::GetPropertyString(std::string name)//получить имя в виде строки.вроде понятно
{
	return properties[name];
}

sf::Vector2i Level::GetTileSize()
{
	return sf::Vector2i(this->tileRect.width, this->tileRect.height);
}

bool Level::LoadFromFile(std::string filename)//двоеточия-обращение к методам класса вне класса 
{
	TiXmlDocument levelFile(filename.c_str());//загружаем файл в TiXmlDocument
											  // загружаем XML-карту
	if (!levelFile.LoadFile())//если не удалось загрузить карту
	{
		std::cout << "Loading level \"" << filename << "\" failed." << std::endl;//выдаем ошибку
		return false;
	}
	// работаем с контейнером map
	TiXmlElement* map;
	map = levelFile.FirstChildElement("map");
	// пример карты: <map version="1.0" orientation="orthogonal"
	// width="10" height="10" tilewidth="34" tileheight="34">


	//извлекаем из нашей карты ее свойства
	//те свойства, которые задавали при работе в 
	//тайлмап редакторе
	this->tileRect = sf::IntRect(
		atoi(map->Attribute("width")),
		atoi(map->Attribute("height")),
		atoi(map->Attribute("tilewidth")),
		atoi(map->Attribute("tileheight")) 
		);

	// Берем описание тайлсета и идентификатор первого тайла
	TiXmlElement* tilesetElement;
	tilesetElement = map->FirstChildElement("tileset");
	firstTileID = atoi(tilesetElement->Attribute("firstgid"));
	// source - путь до картинки в контейнере image
	TiXmlElement* image;
	image = tilesetElement->FirstChildElement("image");
	std::string imagepath = image->Attribute("source");
	// пытаемся загрузить тайлсет
	sf::Image img;
	if (!img.loadFromFile(imagepath))
	{
		std::cout << "Failed to load tile sheet." << std::endl;//если не удалось загрузить тайлсет-выводим ошибку в консоль
		return false;
	}
	img.createMaskFromColor(sf::Color(255, 255, 255));//для маски цвета.сейчас нет маски
	tilesetImage.loadFromImage(img);
	tilesetImage.setSmooth(true);//сглаживание
								  // получаем количество столбцов и строк тайлсета
	int columns = tilesetImage.getSize().x / tileRect.width;
	int rows = tilesetImage.getSize().y / tileRect.height;
	// вектор из прямоугольников изображений (TextureRect)
	std::vector<sf::Rect<int>> subRects;
	for (int y = 0; y < rows; y++)
		for (int x = 0; x < columns; x++)
		{
			sf::IntRect rect;
			rect.top = y * tileRect.height;
			rect.height = tileRect.height;
			rect.left = x * tileRect.width;
			rect.width = tileRect.width;
			subRects.push_back(rect);
		}
	// работа со слоями
	TiXmlElement* layerElement;
	layerElement = map->FirstChildElement("layer");
	while (layerElement)
	{
		Layer layer;
		// если присутствует opacity, то задаем прозрачность слоя, иначе он полностью непрозрачен
		if (layerElement->Attribute("opacity") != NULL)
		{
			double opacity = strtod(layerElement->Attribute("opacity"), NULL);
			layer.opacity = 255 * opacity;
		}
		else
		{
			layer.opacity = 255;
		}
		//  контейнер <data> 
		TiXmlElement* layerDataElement;
		layerDataElement = layerElement->FirstChildElement("data");
		if (layerDataElement == NULL)
		{
			std::cout << "Bad map. No layer information found." << std::endl;
		}
		//  контейнер <tile> - описание тайлов каждого слоя
		TiXmlElement* tileElement;
		tileElement = layerDataElement->FirstChildElement("tile");
		if (tileElement == NULL)
		{
			std::cout << "Bad map. No tile information found." << std::endl;
			return false;
		}
		int x = 0;
		int y = 0;
		while (tileElement)
		{
			int subRectToUse = 0;
			int tileGID = -1;
			if (!(tileElement->Attribute("gid") == NULL))
			{
				tileGID = 0;
				tileGID = atoi(tileElement->Attribute("gid"));
				subRectToUse = tileGID - firstTileID;
				// Устанавливаем TextureRect каждого тайла
				if (subRectToUse >= 0)
				{
					sf::Sprite sprite;
					sprite.setTexture(tilesetImage);
					sprite.setTextureRect(subRects[subRectToUse]);
					sprite.setPosition(x * tileRect.width, y * tileRect.height);
					sprite.setColor(sf::Color(255, 255, 255, layer.opacity));
					layer.tiles.push_back(sprite);//закидываем в слой спрайты тайлов
				}
			}

			x++;
			if (x >= tileRect.left)
			{
				x = 0;
				y++;
				if (y >= tileRect.top)
					y = 0;
			}
			tileElement = tileElement->NextSiblingElement("tile");
		}
		layers.push_back(layer);
		layerElement = layerElement->NextSiblingElement("layer");
	}
	// работа с объектами
	TiXmlElement* objectGroupElement;
	// если есть слои объектов
	if (map->FirstChildElement("objectgroup") != NULL)
	{
		objectGroupElement = map->FirstChildElement("objectgroup");
		while (objectGroupElement)
		{
			//  контейнер <object>
			TiXmlElement* objectElement;
			objectElement = objectGroupElement->FirstChildElement("object");
			while (objectElement)
			{
				// получаем все данные - тип, имя, позиция, и тд
				std::string objectType;
				if (objectElement->Attribute("type") != NULL)
				{
					objectType = objectElement->Attribute("type");
				}
				std::string objectName;
				if (objectElement->Attribute("name") != NULL)
				{
					objectName = objectElement->Attribute("name");
				}
				int x = atoi(objectElement->Attribute("x"));
				int y = atoi(objectElement->Attribute("y"));
				int width, height;
				sf::Sprite sprite;
				sprite.setTexture(tilesetImage);
				sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
				sprite.setPosition(x, y);
				if (objectElement->Attribute("width") != NULL)
				{
					width = atoi(objectElement->Attribute("width"));
					height = atoi(objectElement->Attribute("height"));
				}
				else
				{
					width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
					height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
					sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
				}
				// экземпляр объекта
				Object object;
				object.name = objectName;
				object.type = objectType;
				object.sprite = sprite;
				sf::Rect <float> objectRect;
				objectRect.top = static_cast<float>(y);
				objectRect.left = static_cast<float>(x);
				objectRect.height = static_cast<float>(height);
				objectRect.width = static_cast<float>(width);
				object.rect = static_cast<sf::FloatRect>(objectRect);
				// "переменные" объекта
				TiXmlElement* properties;
				properties = objectElement->FirstChildElement("properties");
				if (properties != NULL)
				{
					TiXmlElement* prop;
					prop = properties->FirstChildElement("property");
					if (prop != NULL)
					{
						while (prop)
						{
							std::string propertyName = prop->Attribute("name");
							std::string propertyValue = prop->Attribute("value");
							object.properties[propertyName] = propertyValue;
							prop = prop->NextSiblingElement("property");
						}
					}
				}
				objects.push_back(object);
				objectElement = objectElement->NextSiblingElement("object");
			}
			objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
		}
	}
	else
	{
		std::cout << "No object layers found..." << std::endl;
	}
	return true;
}

Object Level::GetObject(std::string name)
{
	// только первый объект с заданным именем
	for (int i = 0; i < objects.size(); i++)
		if (objects[i].name == name)
			return objects[i];
}

std::vector<Object> Level::GetObjects(std::string name)
{
	// все объекты с заданным именем
	std::vector<Object> vec;
	for (int i = 0; i < objects.size(); i++)
		if (objects[i].name == name)
			vec.push_back(objects[i]);
	return vec;
}

std::vector<Object> Level::GetAllObjects()
{
	return this->objects;
}

void Level::Draw(sf::RenderTarget* target)
{
	// рисуем все тайлы (объекты не рисуем!)
	for (int layer = 0; layer < layers.size(); layer++)
	{
		for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
		{
			target->draw(layers[layer].tiles[tile]);
		}
	}
}





void TileMap::initVariabless()
{
	this->gridsize = 0;
	this->xmlmap = NULL;
	this->xmlTilesetElement = NULL;
	this->xmlImage = NULL;
	this->xmlLayerElement = NULL;
	this->xmlLayerDataElement = NULL;
	this->xmlTileElement = NULL;
	this->xmlObjectGroupElement = NULL;
	this->xmlObjectElement = NULL;
	this->xmlProperties = NULL;
	this->xmlProperty = NULL;
}

TileMap::TileMap()
{
	this->initVariabless();
}

TileMap::~TileMap()
{
	delete this->xmlmap;
	delete this->xmlTilesetElement;
	delete this->xmlImage;
	delete this->xmlLayerElement;
	delete this->xmlLayerDataElement;
	delete this->xmlTileElement;
	delete this->xmlObjectGroupElement;
	delete this->xmlObjectElement;
	delete this->xmlProperties;
	delete this->xmlProperty;
}

void TileMap::initMap()
{
	this->xmlmap= this->levelFile.FirstChildElement("map");

	this->tileRect = sf::IntRect(
		atoi(this->xmlmap->Attribute("width")),
		atoi(this->xmlmap->Attribute("height")),
		atoi(this->xmlmap->Attribute("tilewidth")),
		atoi(this->xmlmap->Attribute("tileheight"))
		);
}

void TileMap::initElements()
{
	this->xmlTilesetElement = this->xmlmap->FirstChildElement("tileset");
	this->firstTileID = atoi(this->xmlTilesetElement->Attribute("firstgid"));
}

void TileMap::initImage(bool smooth)
{
	this->xmlImage = this->xmlTilesetElement->FirstChildElement("image");
	this->imagepath = this->xmlImage->Attribute("source");

	if (!this->image.loadFromFile(this->imagepath))
		throw "Failed to load tile sheet.";

	this->tilesetImage.loadFromImage(this->image);
	this->tilesetImage.setSmooth(smooth);
}

void TileMap::initSizeMap()
{
	this->countMap = sf::Vector2i(
		this->tilesetImage.getSize().x / this->tileRect.width,
		this->tilesetImage.getSize().y / this->tileRect.height
		);

	for (size_t x = 0; x < this->countMap.x; x++)
	{
		for (size_t y = 0; y < this->countMap.y; y++)
		{
			sf::IntRect rect;
			rect.top = y * tileRect.height;
			rect.height = tileRect.height;
			rect.left = x * tileRect.width;
			rect.width = tileRect.width;
			subRects.push_back(rect);
		}
	}
}

void TileMap::initObjectsMap()
{
	this->xmlLayerElement = this->xmlmap->FirstChildElement("layer");
	while (this->xmlLayerElement)
	{

	}
}

bool TileMap::loadMapFromFile(std::string path, float gridsize,bool smooth)
{
	this->levelFile = path.c_str();

	if (this->levelFile.LoadFile())
	{
		this->initMap();
		this->initElements();
		this->initImage(smooth);
		this->initSizeMap();
		this->initObjectsMap();




	}
	else
	{
		std::cout << "Loading level \"" << path << "\" failed." << std::endl;
		return false;
	}
	return true;
}

