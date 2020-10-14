#include "FileSys.h"

bool nvs::myFileSystem::checkFile(std::string path)
{
	std::ifstream ifs(path);

	if (ifs.is_open())
	{
		ifs.close();
		return true;
	}
	else
		return false;	
}

nvs::myFileSystem::myFileSystem()
{

}

nvs::myFileSystem::~myFileSystem()
{
}

void nvs::myFileSystem::save(std::string path, sf::Vector2f* data)
{
	std::ofstream ofs(path);

	if (ofs.is_open())
	{
		ofs << data->x << std::endl;
		ofs << data->y << std::endl;
	}
	ofs.close();
}

void nvs::myFileSystem::load(std::string path)
{
}
