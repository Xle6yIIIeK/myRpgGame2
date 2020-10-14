#ifndef TILEMAPCORE_H
#define TILEMAPCORE_H
#include "stdafx.h"

struct Object
{
	int GetPropertyInt(std::string name);				//номер свойства объекта в нашем списке
	float GetPropertyFloat(std::string name);
	std::string GetPropertyString(std::string name);
	std::string name;									//объ€вили переменную name типа string
	std::string type;									//а здесь переменную type типа string
	sf::Rect<float> rect;								//тип Rect с нецелыми значени€ми
	std::map<std::string, std::string> properties;		//создаЄм ассоциатиный массив. ключ - строковый тип, значение - строковый
	sf::Sprite sprite;									//объ€вили спрайт
};

struct Layer				//слои
{
	double opacity;								//непрозрачность сло€
	std::vector<sf::Sprite> tiles;				//закидываем в вектор тайлы
};

class Level										//главный класс - уровень
{
private:
	sf::IntRect tileRect;				//в tmx файле width height в начале,затем размер тайла
	int firstTileID;											//получаем айди первого тайла
	sf::Rect<float> drawingBounds;								//размер части карты которую рисуем
	sf::Texture tilesetImage;									//текстура карты
	std::vector<Object> objects;								//массив типа ќбъекты, который мы создали
	std::vector<Layer> layers;
public:
	bool LoadFromFile(std::string filename);					//возвращает false если не получилось загрузить
	Object GetObject(std::string name);
	std::vector<Object> GetObjects(std::string name);			//выдаем объект в наш уровень
	std::vector<Object> GetAllObjects();						//выдаем все объекты в наш уровень
	void Draw(sf::RenderTarget* target);						//рисуем в окно
	sf::Vector2i GetTileSize();									//получаем размер тайла

};

class TileMap
{
	private:
		float gridsize;
		//tiny xml 
		TiXmlDocument levelFile;
		TiXmlElement* xmlmap;
		sf::IntRect tileRect;
		TiXmlElement* xmlTilesetElement;
		int    firstTileID;
		TiXmlElement* xmlImage;
		std::string imagepath;
		sf::Image image;
		sf::Texture tilesetImage;
		sf::Vector2i countMap;
		std::vector<sf::IntRect> subRects;
		TiXmlElement* xmlLayerElement;
		TiXmlElement* xmlLayerDataElement;
		TiXmlElement* xmlTileElement;
		sf::Sprite sprite;
		TiXmlElement* xmlObjectGroupElement;
		TiXmlElement* xmlObjectElement;
		std::string objectType;
		std::string objectName;
		sf::Sprite objectsprite;
		TiXmlElement* xmlProperties;
		TiXmlElement* xmlProperty;
		std::string propertyName;
		std::string propertyValue;

		void initVariabless();
		void initMap();
		void initElements();
		void initImage(bool smooth);
		void initSizeMap();
		void initObjectsMap();

	public:
		TileMap();
		virtual ~TileMap();

		bool loadMapFromFile(std::string path,float gridsize, bool smooth);
	   

};
#endif // TILEMAPCORE_H