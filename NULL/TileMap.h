#ifndef TILEMAPCORE_H
#define TILEMAPCORE_H
#include "stdafx.h"

struct Object
{
	int GetPropertyInt(std::string name);				//����� �������� ������� � ����� ������
	float GetPropertyFloat(std::string name);
	std::string GetPropertyString(std::string name);
	std::string name;									//�������� ���������� name ���� string
	std::string type;									//� ����� ���������� type ���� string
	sf::Rect<float> rect;								//��� Rect � �������� ����������
	std::map<std::string, std::string> properties;		//������ ������������ ������. ���� - ��������� ���, �������� - ���������
	sf::Sprite sprite;									//�������� ������
};

struct Layer				//����
{
	double opacity;								//�������������� ����
	std::vector<sf::Sprite> tiles;				//���������� � ������ �����
};

class Level										//������� ����� - �������
{
private:
	sf::IntRect tileRect;				//� tmx ����� width height � ������,����� ������ �����
	int firstTileID;											//�������� ���� ������� �����
	sf::Rect<float> drawingBounds;								//������ ����� ����� ������� ������
	sf::Texture tilesetImage;									//�������� �����
	std::vector<Object> objects;								//������ ���� �������, ������� �� �������
	std::vector<Layer> layers;
public:
	bool LoadFromFile(std::string filename);					//���������� false ���� �� ���������� ���������
	Object GetObject(std::string name);
	std::vector<Object> GetObjects(std::string name);			//������ ������ � ��� �������
	std::vector<Object> GetAllObjects();						//������ ��� ������� � ��� �������
	void Draw(sf::RenderTarget* target);						//������ � ����
	sf::Vector2i GetTileSize();									//�������� ������ �����

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